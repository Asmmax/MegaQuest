from pathlib import PurePath
from pathlib import Path
from generator import DirEnvironment
from generator import Property
from generator import Method
from generator import Base
from generator import Dependency
from generator import ClassesGateway
from generator import SerializableEnum
from generator import SharedClass
from generator import SharedInterface
from generator import PolymorphicClass
from generator import PolymorphicInterface
from generator import SimpleClass
from changes_list import ChangesList
import clang.cindex
import pickle


class TypeUtils:
    @staticmethod
    def get_pure_type_name(node):
        type_name = node.type.get_canonical().spelling.replace('&', '').strip()

        type_name = type_name.replace('const', '', 1).strip()

        return type_name.replace('std::weak_ptr', 'std::shared_ptr', 1).strip()

    @staticmethod
    def clean_up(raw_str):
        redundant = ['std::vector', 'std::shared_ptr']
        for expr in redundant:
            if raw_str.startswith(expr):
                raw_str = raw_str.removeprefix(expr)
                raw_str = raw_str.removeprefix('<')
                raw_str = raw_str.removesuffix('>')
                TypeUtils.clean_up(raw_str)
        return raw_str


class TagContainer:
    def __init__(self, node):
        self.__tags = {}
        self.__read_tags(node)

    def has_tag(self, tag_name):
        return tag_name in self.__tags.keys()

    def get_tag_args(self, tag_name):
        return self.__tags[tag_name]

    def get_first_tag_arg(self, tag_name):
        tag_args = self.get_tag_args(tag_name)
        assert tag_args
        return tag_args[0]

    def remove_tag(self, tag_name):
        self.__tags.pop(tag_name)

    def replace_tags(self, tags: dict):
        if tags is None:
            return
        for name, args in tags.items():
            self.__tags[name] = args

    def __read_tags(self, node):
        self.__read_inherited_tags(node)
        tags = self.__parse_tags(node.raw_comment)
        self.replace_tags(tags)

    def __read_inherited_tags(self, node):
        for child in node.get_children():
            if child.kind != clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                continue
            base = child.type.get_declaration().get_definition()
            self.__read_inherited_tags(base)
            base_tags = self.__parse_tags(base.raw_comment)
            if base_tags is not None:
                inherited_base_tags = TagContainer.__filter_inherited_tags(base_tags)
                self.replace_tags(inherited_base_tags)

    @staticmethod
    def __parse_tags(comment: str):
        tags = {}
        if not comment:
            return
        raw_tags = comment.replace('///', ' ').split('@')
        for raw_tag in raw_tags:
            tag_with_args = raw_tag.split()
            if tag_with_args:
                tag_args = []
                tag_name = tag_with_args.pop(0)
                if tag_with_args:
                    for arg in tag_with_args.pop(0).split(','):
                        tag_args.append(arg)
                tags[tag_name] = tag_args
        return tags

    inherited_tags = ['shared', 'polymorphic']

    @staticmethod
    def __filter_inherited_tags(tags: dict):
        filtered_tags = {}
        for name, args in tags.items():
            if name in TagContainer.inherited_tags:
                filtered_tags[name] = args
        return filtered_tags


class EnumInfo:
    def __init__(self, node):
        self.filename = node.translation_unit.spelling
        self.full_type_name = node.type.spelling
        self.elements = []
        for elem in node.get_children():
            self.elements.append(elem.spelling)


class BaseInfo:
    def __init__(self, full_type_name):
        self.full_type_name = full_type_name


class ClassInfo:
    def __init__(self, node):
        self.filename = node.translation_unit.spelling
        self.type_name = node.spelling
        self.full_type_name = node.type.spelling

        self.bases = ClassInfo.find_bases(node)
        self.properties = ClassInfo.find_properties(node)
        self.methods = ClassInfo.find_methods(node)
        self.tags = TagContainer(node)

    @staticmethod
    def find_bases_as_nodes(node):
        bases = []
        for child in node.get_children():
            if child.kind != clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                continue
            bases.append(child)
        return bases

    @staticmethod
    def find_bases(node):
        bases = []
        for child in ClassInfo.find_bases_as_nodes(node):
            base = child.type.get_declaration()
            new_base = BaseInfo(base.type.spelling)
            bases.append(new_base)
        return bases

    @staticmethod
    def get_suit_constructor(node):
        suit_children = []
        for child in node.get_children():
            if child.kind != clang.cindex.CursorKind.CONSTRUCTOR:
                continue

            if child.is_copy_constructor():
                continue

            if child.is_move_constructor():
                continue

            suit_children.append(child)

        if not suit_children:
            return None

        for child in suit_children:
            if TagContainer(child).has_tag('inject'):
                return child

        return suit_children[0]

    @staticmethod
    def find_properties(node):
        properties = []
        constructor = ClassInfo.get_suit_constructor(node)
        if constructor:
            args = constructor.get_arguments()
        else:
            args = node.type.get_fields()

        for arg in args:
            if arg.access_specifier in [clang.cindex.AccessSpecifier.PRIVATE, clang.cindex.AccessSpecifier.PROTECTED]:
                continue
            clean_arg_type = TypeUtils.get_pure_type_name(arg)
            new_prop = Property(arg.spelling, clean_arg_type)
            properties.append(new_prop)
        return properties

    @staticmethod
    def find_methods(node):
        methods = []
        for base_as_node in ClassInfo.find_bases_as_nodes(node):
            for base_method in ClassInfo.find_methods(base_as_node.type.get_declaration()):
                methods.append(base_method)
        for method in ClassInfo.get_methods(node):
            method_name = method.spelling
            raw_args = method.get_arguments()
            args = []
            for raw_arg in raw_args:
                clean_arg_type = TypeUtils.get_pure_type_name(raw_arg)
                prop = Property(raw_arg.spelling, clean_arg_type)
                args.append(prop)
            new_method = Method(method_name, args)
            methods.append(new_method)
        return methods

    @staticmethod
    def get_methods(node):
        methods = []
        for child in node.get_children():
            if child.kind != clang.cindex.CursorKind.CXX_METHOD:
                continue
            if child.access_specifier in [clang.cindex.AccessSpecifier.PRIVATE, clang.cindex.AccessSpecifier.PROTECTED]:
                continue
            if not TagContainer(child).has_tag('inject'):
                continue
            methods.append(child)
        return methods


class SerializableClassFactory:
    @staticmethod
    def create_class(filename, type_name, full_type_name, bases, properties, methods, dependencies, tags: TagContainer):
        if tags.has_tag('shared'):
            if not tags.has_tag('abstract'):
                shared_name = tags.get_first_tag_arg('shared')
                return SharedClass(filename, type_name, full_type_name, bases, properties, methods, dependencies,
                                   shared_name)
            return SharedInterface(filename, type_name, full_type_name, bases, properties, methods, dependencies)
        elif tags.has_tag('polymorphic'):
            if not tags.has_tag('abstract'):
                return PolymorphicClass(filename, type_name, full_type_name, bases, properties, methods, dependencies)
            return PolymorphicInterface(filename, type_name, full_type_name, bases, properties, methods, dependencies)
        else:
            return SimpleClass(filename, type_name, full_type_name, bases, properties, methods, dependencies)


class ClassesInfoGateway:
    def read(self, files: list[Path]):
        pass

    def get_enums(self) -> list[EnumInfo]:
        pass

    def get_classes(self) -> list[ClassInfo]:
        pass

    def get_includes(self) -> dict:
        pass


class Analyzer(ClassesInfoGateway):
    def __init__(self, path_utils: DirEnvironment):
        self.__path_utils = path_utils
        self.__enums_info = []
        self.__classes_info = []
        self.__includes = {}

    def read(self, files: list[Path]):
        self._reset()
        print('Analysis of input files...')
        for path in files:
            print('Analysis file ' + str(path))
            index = clang.cindex.Index.create()
            arg_list = ['-std=c++17', '-I' + str(self.__path_utils.working_env_in_path)]
            for add_include in self.__path_utils.add_includes:
                add_include_path = PurePath(add_include)
                arg_list.append('-I' + str(add_include_path))
            options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE \
                      | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES \
                      | clang.cindex.TranslationUnit.PARSE_PRECOMPILED_PREAMBLE
            translation_unit = index.parse(str(path), args=arg_list, options=options)
            self._analyze_unit(translation_unit.cursor)
        for file in files:
            self.__includes[file] = self.__path_utils.get_gen_relative_include_path(file)

    def get_enums(self) -> list[EnumInfo]:
        return self.__enums_info

    def get_classes(self) -> list[ClassInfo]:
        return self.__classes_info

    def get_includes(self) -> dict:
        return self.__includes

    def _reset(self):
        self.__enums_info = []
        self.__classes_info = []
        self.__includes = {}

    def _analyze_unit(self, root: clang.cindex.Cursor):
        for child in root.get_children():
            current_filename = child.translation_unit.spelling
            if child.location.file.name != current_filename:
                continue

            if child.kind == clang.cindex.CursorKind.NAMESPACE:
                self._analyze_unit(child)
                continue

            if not TagContainer(child).has_tag('serializable'):
                continue

            if child.kind == clang.cindex.CursorKind.ENUM_DECL:
                self._add_enum(child)

            if child.kind in [clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL]:
                self._add_class(child)

    def _add_enum(self, node: clang.cindex.Cursor):
        new_enum = EnumInfo(node)
        self.__enums_info.append(new_enum)

    def _add_class(self, node: clang.cindex.Cursor):
        new_class = ClassInfo(node)
        self.__classes_info.append(new_class)


class Cache:
    def __init__(self, enums_info: list[EnumInfo], classes_info: list[ClassInfo], includes: dict):
        self.enums_info = enums_info
        self.classes_info = classes_info
        self.includes = includes


class CachedAnalyzer(ClassesInfoGateway):
    def __init__(self, path_utils: DirEnvironment):
        self.__path_utils = path_utils
        self.__analyzer = Analyzer(path_utils)
        self.__enums_info = []
        self.__classes_info = []
        self.__includes = {}

    def read(self, files: list[Path]):
        self._reset()
        self._read_cache()
        self._remove_non_existent()
        changed_files = self._get_changes(files)
        self._remove_old_info(changed_files)
        self.__analyzer.read(changed_files)
        self.__add_enums(self.__analyzer.get_enums())
        self.__add_classes(self.__analyzer.get_classes())
        self.__add_includes(self.__analyzer.get_includes())
        self._write_cache()
        self._read_sub_caches()

    def get_enums(self) -> list[EnumInfo]:
        return self.__enums_info

    def get_classes(self) -> list[ClassInfo]:
        return self.__classes_info

    def get_includes(self) -> dict:
        return self.__includes

    def has_class(self, full_type_name: str):
        for class_info in self.__classes_info:
            if full_type_name == class_info.full_type_name:
                return True
        return False

    def has_enum(self, full_type_name: str):
        for enum_info in self.__enums_info:
            if full_type_name == enum_info.full_type_name:
                return True
        return False

    def _reset(self):
        self.__enums_info = []
        self.__classes_info = []
        self.__includes = {}

    def _read_cache(self):
        cache_file_name = 'analyzer.cache'
        cache_path = PurePath(self.__path_utils.cache_path).joinpath(cache_file_name)
        if not Path(cache_path).exists():
            return
        with open(cache_path, 'rb') as cache_file:
            cache = pickle.load(cache_file)
            self.__enums_info = cache.enums_info
            self.__classes_info = cache.classes_info
            self._includes = cache.includes

    def _read_sub_caches(self):
        cache_file_name = 'analyzer.cache'
        for sub_cache_path in self.__path_utils.extra_cache_paths:
            cache_path = PurePath(sub_cache_path).joinpath(cache_file_name)
            if not Path(cache_path).exists():
                continue
            with open(cache_path, 'rb') as cache_file:
                cache = pickle.load(cache_file)
                self.__add_enums(cache.enums_info)
                self.__add_classes(cache.classes_info)
                self.__add_includes(cache.includes)

    def _remove_non_existent(self):
        new_enums_info = []
        for enum_info in self.__enums_info:
            if Path(enum_info.filename).exists():
                new_enums_info.append(enum_info)
        self.__enums_info = new_enums_info

        new_classes_info = []
        for class_info in self.__classes_info:
            if Path(class_info.filename).exists():
                new_classes_info.append(class_info)
        self.__classes_info = new_classes_info

    def _remove_old_info(self, files: list[Path]):
        new_enums_info = []
        for enum_info in self.__enums_info:
            enum_file_path = Path(enum_info.filename)
            if enum_file_path not in files:
                new_enums_info.append(enum_info)
        self.__enums_info = new_enums_info

        new_classes_info = []
        for class_info in self.__classes_info:
            class_file_path = Path(class_info.filename)
            if class_file_path not in files:
                new_classes_info.append(class_info)
        self.__classes_info = new_classes_info

    def _write_cache(self):
        cache_file_name = 'analyzer.cache'
        cache_path = Path(self.__path_utils.cache_path)
        if not cache_path.exists():
            cache_path.mkdir(parents=True)
        cache_file_path = cache_path.joinpath(cache_file_name)
        cache = Cache(self.__enums_info, self.__classes_info, self.__includes)
        with open(cache_file_path, 'wb') as cache_file:
            pickle.dump(cache, cache_file)

    def _get_changes(self, files: list[Path]) -> list[Path]:
        cache_path = Path(self.__path_utils.cache_path)
        changes_list = ChangesList.get_or_create_changes_list(cache_path)
        return changes_list.get_changes(files)

    def __add_enums(self, new_enums: list[EnumInfo]):
        self.__enums_info.extend(new_enums)
        unique_enums = {}
        for enum_info in self.__enums_info:
            unique_enums[enum_info.full_type_name] = enum_info
        self.__enums_info.clear()
        for key, unique_enum in unique_enums.items():
            self.__enums_info.append(unique_enum)

    def __add_classes(self, new_classes: list[ClassInfo]):
        self.__classes_info.extend(new_classes)
        unique_classes = {}
        for class_info in self.__classes_info:
            unique_classes[class_info.full_type_name] = class_info
        self.__classes_info.clear()
        for key, unique_class in unique_classes.items():
            self.__classes_info.append(unique_class)

    def __add_includes(self, new_includes: dict):
        for file, new_include in new_includes.items():
            self.__includes[file] = new_include


class ClassesConverter(ClassesGateway):
    def __init__(self, analyzer: ClassesInfoGateway):
        super(ClassesConverter, self).__init__()
        self.analyzer = analyzer
        self.enums_info = []
        self.classes_info = []
        self.includes = {}

    def get_enum_info(self, full_type_name):
        clean_type_name = TypeUtils.clean_up(full_type_name)
        for enum_info in self.enums_info:
            if clean_type_name == enum_info.full_type_name:
                return enum_info
        return None

    def get_class_info(self, full_type_name):
        clean_type_name = TypeUtils.clean_up(full_type_name)
        for _class_info in self.classes_info:
            if clean_type_name == _class_info.full_type_name:
                return _class_info
        return None

    def get_include(self, filename: str):
        file_path = Path(filename)
        if file_path in self.includes.keys():
            return self.includes[file_path]
        return None

    def _init(self, files: list[Path]):
        self.analyzer.read(files)
        self.enums_info = self.analyzer.get_enums()
        self.classes_info = self.analyzer.get_classes()
        self.includes = self.analyzer.get_includes()

    def _get_enums_names(self) -> list[str]:
        names = []
        for enum_info in self.enums_info:
            names.append(enum_info.full_type_name)
        return names

    def _read_enum(self, enum_name: str):
        info = self.get_enum_info(enum_name)
        if info is None:
            return
        new_enum = SerializableEnum(info.filename, info.full_type_name, info.elements)
        self._add_enum(new_enum)

    def _get_classes_names(self) -> list[str]:
        names = []
        for class_info in self.classes_info:
            names.append(class_info.full_type_name)
        return names

    def _read_class(self, class_name: str):
        info = self.get_class_info(class_name)
        if info is None:
            return
        bases = self.__prepare_bases(info)
        dependencies = self.__get_all_dependencies(info)
        new_class = SerializableClassFactory.create_class(info.filename, info.type_name, info.full_type_name, bases,
                                                          info.properties, info.methods, dependencies, info.tags)
        self._add_class(new_class)

    def __prepare_bases(self, info: ClassInfo):
        new_bases = []
        for base_info in info.bases:
            base_class_info = self.get_class_info(base_info.full_type_name)
            if base_class_info:
                parents = self.__prepare_bases(base_class_info)
                new_base = Base(base_info.full_type_name, True, parents)
                new_bases.append(new_base)
            else:
                new_base = Base(base_info.full_type_name, False, [])
                new_bases.append(new_base)
        return new_bases

    def __get_all_dependencies(self, info: ClassInfo):
        dependencies = []
        for base in info.bases:
            clean_base_type = TypeUtils.clean_up(base.full_type_name)
            base_class = self.get_class(clean_base_type)
            if base_class:
                dependency = Dependency(base_class.filename, self.get_include(base_class.filename))
                dependencies.append(dependency)

        for _property in info.properties:
            clean_property_type = TypeUtils.clean_up(_property.full_type_name)
            property_class = self.get_class(clean_property_type)
            if property_class:
                dependency = Dependency(property_class.filename, self.get_include(property_class.filename))
                dependencies.append(dependency)
            property_enum = self.get_enum(clean_property_type)
            if property_enum:
                dependency = Dependency(property_enum.filename, self.get_include(property_enum.filename))
                dependencies.append(dependency)

        for method in info.methods:
            clean_method_type = TypeUtils.clean_up(method.full_type_name)
            method_class = self.get_class(clean_method_type)
            if method_class:
                dependency = Dependency(method_class.filename, self.get_include(method_class.filename))
                dependencies.append(dependency)
            method_enum = self.get_enum(clean_method_type)
            if method_enum:
                dependency = Dependency(method_enum.filename, self.get_include(method_enum.filename))
                dependencies.append(dependency)

        return dependencies
