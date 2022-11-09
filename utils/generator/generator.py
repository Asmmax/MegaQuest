from pathlib import Path
from pathlib import PurePath
import clang.cindex
from string import Template

property_tpl_path = 'templates/property.tpl'
impl_tpl_path = 'templates/impl.tpl'

enum_decl_tpl_path = 'templates/Enum/decl.tpl'
enum_def_tpl_path = 'templates/Enum/def.tpl'
enum_value_tpl_path = 'templates/Enum/value.tpl'

simple_decl_tpl_path = 'templates/Simple/decl.tpl'
simple_def_tpl_path = 'templates/Simple/def.tpl'

polymorphic_impl_decl_tpl_path = 'templates/Polymorphic/impl_decl.tpl'
polymorphic_interface_decl_tpl_path = 'templates/Polymorphic/interface_decl.tpl'
polymorphic_impl_def_tpl_path = 'templates/Polymorphic/impl_def.tpl'
polymorphic_interface_def_tpl_path = 'templates/Polymorphic/interface_def.tpl'
polymorphic_bind_using_tpl_path = 'templates/Polymorphic/bind_using.tpl'

shared_interface_decl_tpl_path = 'templates/Shared/interface_decl.tpl'
shared_interface_def_tpl_path = 'templates/Shared/interface_def.tpl'
shared_impl_decl_tpl_path = 'templates/Shared/impl_decl.tpl'
shared_impl_def_tpl_path = 'templates/Shared/impl_def.tpl'
shared_method_tpl_path = 'templates/Shared/method.tpl'
shared_bind_using_tpl_path = 'templates/Shared/bind_using.tpl'


class Tag:
    name = ''
    args = []


class TagUtils:
    inherited_tags = ['shared', 'polymorphic']

    @staticmethod
    def has_tag(node, tag_name):
        comment = node.raw_comment
        tags = []
        if comment:
            tags = comment.split()

        return tags.count('@' + tag_name) > 0

    @staticmethod
    def consist_tag(tags, tag_name):
        for tag in tags:
            if tag.name == tag_name:
                return True
        return False

    @staticmethod
    def get_tag(tags, tag_name):
        for tag in tags:
            if tag.name == tag_name:
                return tag
        return None

    @staticmethod
    def remove_tag(tags, tag_name):
        remove_list = []
        for tag in tags:
            if tag.name == tag_name:
                remove_list.append(tag)
        for removed_tag in remove_list:
            tags.remove(removed_tag)

    @staticmethod
    def parse_tags(comment):
        tags = []
        if not comment:
            return tags

        raw_tags = comment.replace('///', ' ').split('@')
        for raw_tag in raw_tags:
            tag_with_args = raw_tag.split()
            if tag_with_args:
                new_tag = Tag()
                new_tag.name = tag_with_args.pop(0)
                if tag_with_args:
                    new_tag.args = []
                    for arg in tag_with_args.pop(0).split(','):
                        new_tag.args.append(arg)
                tags.append(new_tag)
        return tags

    @staticmethod
    def replace_tag(source_tag, destination_tag):
        if source_tag.args == destination_tag.args:
            return
        if not destination_tag.args:
            return

        assert not source_tag.args
        source_tag.args = destination_tag.args

    @staticmethod
    def merge_tags(result_tags, input_tags):
        for result_tag in result_tags:
            some_tag = TagUtils.get_tag(input_tags, result_tag.name)
            if some_tag:
                TagUtils.replace_tag(result_tag, some_tag)
                TagUtils.remove_tag(input_tags, some_tag.name)
        for input_tag in input_tags:
            result_tags.append(input_tag)

    @staticmethod
    def get_inherited_tags(node):
        tags = []
        for child in node.get_children():
            if child.kind != clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                continue

            base = child.type.get_declaration().get_definition()
            temp_tags = TagUtils.get_inherited_tags(base)
            base_tags = TagUtils.parse_tags(base.raw_comment)
            for base_tag in base_tags:
                if base_tag.name in TagUtils.inherited_tags:
                    TagUtils.remove_tag(temp_tags, base_tag.name)
                    temp_tags.append(base_tag)
            TagUtils.merge_tags(tags, temp_tags)
        return tags

    @staticmethod
    def get_class_tags(node):
        tags = TagUtils.parse_tags(node.raw_comment)
        base_tags = TagUtils.get_inherited_tags(node)
        for class_tag in tags:
            TagUtils.remove_tag(base_tags, class_tag.name)
        for base_tag in base_tags:
            tags.append(base_tag)
        return tags

    @staticmethod
    def get_tag_arg(tags, tag_name):
        for tag in tags:
            if tag.name == tag_name:
                assert tag.args
                return tag.args[0]


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


class PathUtils:
    def __init__(self, working_env_in_path, working_env_out_include_path, working_env_out_source_path,
                 in_dir, out_include_dir, out_source_dir, add_includes):

        self.working_env_in_path = working_env_in_path
        self.working_env_out_include_path = working_env_out_include_path
        self.working_env_out_source_path = working_env_out_source_path
        self.in_dir = in_dir
        self.out_include_dir = out_include_dir
        self.out_source_dir = out_source_dir
        self.add_includes = add_includes

        self.in_path = PurePath(working_env_in_path).joinpath(in_dir)
        self.out_include_path = PurePath(working_env_out_include_path).joinpath(out_include_dir)
        self.out_source_path = PurePath(working_env_out_source_path).joinpath(out_source_dir)

    def get_gen_path_for(self, path):
        raw_path = PurePath(path).relative_to(self.in_path).with_suffix('')
        filename = raw_path.name
        return raw_path.with_name(filename + '_gen')

    def rm_out_dirs(self):
        PathUtils.rm_tree(self.out_include_path)
        PathUtils.rm_tree(self.out_source_path)

    @staticmethod
    def rm_tree(pth):
        pth = Path(pth)
        if not pth.exists():
            return
        for child in pth.glob('*'):
            if child.is_file():
                child.unlink()
            else:
                PathUtils.rm_tree(child)
        pth.rmdir()

    def relative_to_working_in_env(self, path):
        return PurePath(path).relative_to(self.working_env_in_path)

    def relative_to_working_out_include_env(self, path):
        return PurePath(path).relative_to(self.working_env_out_include_path)

    def get_path_list(self):
        raw_path_list = sorted(Path(self.in_path).rglob('*.hpp'))
        path_list = []
        for raw_path in raw_path_list:
            if PathUtils.suit_file(raw_path):
                path_list.append(raw_path)
        return path_list

    @staticmethod
    def suit_file(path):
        for parent in path.parents:
            if parent.name == ".generated":
                return False
        return True


class SerializableEnum:
    def __init__(self, node):
        self.filename = node.translation_unit.spelling
        self.full_type_name = node.type.spelling
        self.elements = []
        for elem in node.get_children():
            self.elements.append(elem.spelling)

    def fill_header(self, stream):
        enum_hpp_tpl = Template(Path(enum_decl_tpl_path).read_text())

        enum_full_type = self.full_type_name
        stream.write(enum_hpp_tpl.substitute(locals()))

    def fill_source(self, stream):
        enum_cpp_tpl = Template(Path(enum_def_tpl_path).read_text())
        enum_value_cpp_tpl = Template(Path(enum_value_tpl_path).read_text())

        enum_values_list = []
        enum_full_type = self.full_type_name
        for enum_value_name in self.elements:
            enum_value = enum_value_cpp_tpl.substitute(locals())
            enum_values_list.append(enum_value)
        enum_values = ',\n'.join(enum_values_list)
        stream.write(enum_cpp_tpl.substitute(locals()))


class Base:
    def __init__(self, full_type_name):
        self.full_type_name = full_type_name
        self.__classes = []

    def init_classes(self, classes):
        self.__classes = classes

    def get_all_serializable_classes(self):
        return self.__classes


class Property:
    def __init__(self, arg):
        self.arg_name = arg.spelling
        self.full_type_name = TypeUtils.get_pure_type_name(arg)


class Method:
    def __init__(self, method):
        self.name = method.spelling

        args = method.get_arguments()
        for arg in args:
            self.arg_name = arg.spelling
            self.full_type_name = TypeUtils.get_pure_type_name(arg)
            break


class SerializableClass:
    def __init__(self, node):
        self.filename = node.translation_unit.spelling
        self.type_name = node.spelling
        self.full_type_name = node.type.spelling

        self.bases = SerializableClass.find_bases(node)
        self.properties = SerializableClass.find_properties(node)
        self.methods = SerializableClass.find_methods(node)

        self.dependencies = []

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
        for child in SerializableClass.find_bases_as_nodes(node):
            base = child.type.get_declaration()
            new_base = Base(base.type.spelling)
            bases.append(new_base)
        return bases

    @staticmethod
    def find_properties(node):
        properties = []
        constructor = SerializableClass.get_suit_constructor(node)
        if constructor:
            args = constructor.get_arguments()
        else:
            args = node.type.get_fields()

        for arg in args:
            if arg.access_specifier in [clang.cindex.AccessSpecifier.PRIVATE, clang.cindex.AccessSpecifier.PROTECTED]:
                continue
            new_prop = Property(arg)
            properties.append(new_prop)
        return properties

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
            if TagUtils.has_tag(child, 'inject'):
                return child

        return suit_children[0]

    @staticmethod
    def find_methods(node):
        methods = []
        for base_as_node in SerializableClass.find_bases_as_nodes(node):
            for base_method in SerializableClass.find_methods(base_as_node.type.get_declaration()):
                methods.append(base_method)
        for method in SerializableClass.get_methods(node):
            new_method = Method(method)
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
            if not TagUtils.has_tag(child, 'inject'):
                continue
            methods.append(child)
        return methods

    def fill_header(self, stream):
        pass

    def fill_source(self, stream, path_utils):
        pass

    def init_dependencies(self, dependencies):
        self.dependencies = dependencies

    def get_all_serializable_bases(self):
        all_bases = []
        for base in self.bases:
            all_bases.extend(base.get_all_serializable_classes())
        return all_bases


class SharedInterface(SerializableClass):
    def __init__(self, node):
        super(SharedInterface, self).__init__(node)

    def fill_header(self, stream):
        shared_interface_hpp_tpl = Template(Path(shared_interface_decl_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name
        stream.write(shared_interface_hpp_tpl.substitute(locals()))

    def fill_source(self, stream, path_utils):
        shared_interface_cpp_tpl = Template(Path(shared_interface_def_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name
        stream.write(shared_interface_cpp_tpl.substitute(locals()))


class SharedClass(SharedInterface):
    def __init__(self, node, shared_name):
        self.shared_name = shared_name
        super(SharedClass, self).__init__(node)

    def fill_header(self, stream):
        shared_impl_hpp_tpl = Template(Path(shared_impl_decl_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        all_bases_list = []
        for base in self.get_all_serializable_bases():
            all_bases_list.append(', ' + base.full_type_name)
        all_bases = '\n'.join(all_bases_list)

        method_arg_types_list = []
        for method in self.methods:
            method_arg_types_list.append(', ' + method.full_type_name)
        method_arg_types = '\n'.join(method_arg_types_list)

        property_types_list = []
        for _property in self.properties:
            property_types_list.append(', ' + _property.full_type_name)
        property_types = '\n'.join(property_types_list)

        stream.write(shared_impl_hpp_tpl.substitute(locals()))
        super(SharedClass, self).fill_header(stream)

    def fill_source(self, stream, path_utils):
        method_cpp_tpl = Template(Path(shared_method_tpl_path).read_text())
        shared_impl_cpp_tpl = Template(Path(shared_impl_def_tpl_path).read_text())
        container_binder_impl_cpp_tpl = Template(Path(shared_bind_using_tpl_path).read_text())
        property_cpp_tpl = Template(Path(property_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        dependencies_list = []
        for dependency in self.dependencies:
            if dependency.filename == self.filename:
                continue
            gen_path = PurePath(path_utils.out_include_dir). \
                joinpath(path_utils.get_gen_path_for(dependency.filename)).with_suffix('.hpp')
            dependency_include = '#include ' + '"' + str(gen_path).replace('\\', '/') + '"'
            if not dependencies_list.count(dependency_include):
                dependencies_list.append(dependency_include)
        dependencies = '\n'.join(dependencies_list)

        method_list = []
        for method in self.methods:
            full_arg_type_name = method.full_type_name
            arg_name = method.arg_name
            method_name = method.name
            simple_method = method_cpp_tpl.substitute(locals())
            method_list.append(simple_method)
        methods = ',\n'.join(method_list)

        property_list = []
        for _property in self.properties:
            full_arg_type_name = _property.full_type_name
            arg_name = _property.arg_name
            simple_property = property_cpp_tpl.substitute(locals())
            property_list.append(simple_property)
        properties = '\n'.join(property_list)

        base_list = []
        for base in self.get_all_serializable_bases():
            full_base_type_name = base.full_type_name
            container_binder_impl = container_binder_impl_cpp_tpl.substitute(locals())
            base_list.append(container_binder_impl)
        container_binder_impls = '\n'.join(base_list)

        shared_name = self.shared_name

        stream.write(shared_impl_cpp_tpl.substitute(locals()))
        super(SharedClass, self).fill_source(stream, path_utils)


class PolymorphicInterface(SerializableClass):
    def __init__(self, node):
        super(PolymorphicInterface, self).__init__(node)

    def fill_header(self, stream):
        polymorphic_interface_hpp_tpl = Template(Path(polymorphic_interface_decl_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name
        stream.write(polymorphic_interface_hpp_tpl.substitute(locals()))

    def fill_source(self, stream, path_utils):
        polymorphic_interface_cpp_tpl = Template(Path(polymorphic_interface_def_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name
        stream.write(polymorphic_interface_cpp_tpl.substitute(locals()))


class PolymorphicClass(PolymorphicInterface):
    def __init__(self, node):
        super(PolymorphicClass, self).__init__(node)

    def fill_header(self, stream):
        polymorphic_impl_hpp_tpl = Template(Path(polymorphic_impl_decl_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        all_bases_list = []
        for base in self.get_all_serializable_bases():
            all_bases_list.append(', ' + 'std::shared_ptr<' + base.full_type_name + '>')
        all_bases = '\n'.join(all_bases_list)

        property_types_list = []
        for _property in self.properties:
            property_types_list.append(', ' + _property.full_type_name)
        property_types = '\n'.join(property_types_list)

        stream.write(polymorphic_impl_hpp_tpl.substitute(locals()))
        super(PolymorphicClass, self).fill_header(stream)

    def fill_source(self, stream, path_utils):
        polymorphic_impl_cpp_tpl = Template(Path(polymorphic_impl_def_tpl_path).read_text())
        property_cpp_tpl = Template(Path(property_tpl_path).read_text())
        factory_binder_impl_cpp_tpl = Template(Path(polymorphic_bind_using_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        property_list = []
        for _property in self.properties:
            full_arg_type_name = _property.full_type_name
            arg_name = _property.arg_name
            simple_property = property_cpp_tpl.substitute(locals())
            property_list.append(simple_property)
        properties = '\n'.join(property_list)

        base_list = []
        for base in self.get_all_serializable_bases():
            full_base_type_name = base.full_type_name
            factory_binder_impl = factory_binder_impl_cpp_tpl.substitute(locals())
            base_list.append(factory_binder_impl)
        factory_binder_impls = '\n'.join(base_list)

        dependencies_list = []
        for dependency in self.dependencies:
            if dependency.filename == self.filename:
                continue
            gen_path = PurePath(path_utils.out_include_dir). \
                joinpath(path_utils.get_gen_path_for(dependency.filename)).with_suffix('.hpp')
            dependency_include = '#include ' + '"' + str(gen_path).replace('\\', '/') + '"'
            if not dependencies_list.count(dependency_include):
                dependencies_list.append(dependency_include)
        dependencies = '\n'.join(dependencies_list)

        stream.write(polymorphic_impl_cpp_tpl.substitute(locals()))
        super(PolymorphicClass, self).fill_source(stream, path_utils)


class SimpleClass(SerializableClass):
    def __init__(self, node):
        super(SimpleClass, self).__init__(node)

    def fill_header(self, stream):
        simple_hpp_tpl = Template(Path(simple_decl_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        all_bases_list = []
        for base in self.get_all_serializable_bases():
            all_bases_list.append(', ' + base.full_type_name)
        all_bases = '\n'.join(all_bases_list)

        property_types_list = []
        for _property in self.properties:
            property_types_list.append(', ' + _property.full_type_name)
        property_types = '\n'.join(property_types_list)

        stream.write(simple_hpp_tpl.substitute(locals()))

    def fill_source(self, stream, path_utils):
        simple_cpp_tpl = Template(Path(simple_def_tpl_path).read_text())
        property_cpp_tpl = Template(Path(property_tpl_path).read_text())

        type_name = self.type_name
        full_type_name = self.full_type_name

        dependencies_list = []
        for dependency in self.dependencies:
            if dependency.filename == self.filename:
                continue
            gen_path = PurePath(path_utils.out_include_dir). \
                joinpath(path_utils.get_gen_path_for(dependency.filename)).with_suffix('.hpp')
            dependency_include = '#include ' + '"' + str(gen_path).replace('\\', '/') + '"'
            if not dependencies_list.count(dependency_include):
                dependencies_list.append(dependency_include)
        dependencies = '\n'.join(dependencies_list)

        property_list = []
        for _property in self.properties:
            full_arg_type_name = _property.full_type_name
            arg_name = _property.arg_name
            simple_property = property_cpp_tpl.substitute(locals())
            property_list.append(simple_property)
        properties = '\n'.join(property_list)

        stream.write(simple_cpp_tpl.substitute(locals()))


class SerializableClassFactory:
    @staticmethod
    def CreateClass(node):
        tags = TagUtils.get_class_tags(node)
        if TagUtils.consist_tag(tags, 'shared'):
            if not TagUtils.consist_tag(tags, 'abstract'):
                shared_name = TagUtils.get_tag_arg(tags, 'shared')
                return SharedClass(node, shared_name)
            return SharedInterface(node)
        elif TagUtils.consist_tag(tags, 'polymorphic'):
            if not TagUtils.consist_tag(tags, 'abstract'):
                return PolymorphicClass(node)
            return PolymorphicInterface(node)
        else:
            return SimpleClass(node)


class Dependency:
    def __init__(self, filename):
        self.filename = filename


class GenerateUnit:
    def __init__(self, filename, path_utils, enums, sorted_classes):
        self.path_utils = path_utils
        self.origin_path = PurePath(filename)
        self.include_path = PurePath(path_utils.out_include_path).joinpath(
            path_utils.get_gen_path_for(filename)).with_suffix('.hpp')
        self.cpp_path = PurePath(path_utils.out_source_path).joinpath(
            path_utils.get_gen_path_for(filename)).with_suffix(
            '.cpp')

        self.serializable_enums = []
        for enum in enums:
            if PurePath(enum.filename) == PurePath(filename):
                self.serializable_enums.append(enum)

        self.serializable_classes = []
        for sorted_class in sorted_classes:
            if PurePath(sorted_class.filename) == PurePath(filename):
                self.serializable_classes.append(sorted_class)

    def is_valid(self):
        return self.serializable_enums or self.serializable_classes

    def prepare_files(self):
        self.prepare_header_file(self.origin_path, self.include_path)
        self.prepare_source_file(self.include_path, self.cpp_path)

    def prepare_header_file(self, in_path, hpp_path):
        in_include = self.path_utils.relative_to_working_in_env(in_path)
        Path(hpp_path.parent).mkdir(parents=True, exist_ok=True)
        hpp_file = open(hpp_path, 'w')
        hpp_file.write('#pragma once\n')
        hpp_file.write('#include "' + str(in_include).replace('\\', '/') + '"' + '\n')
        hpp_file.close()

    def prepare_source_file(self, hpp_path, cpp_path):
        own_include = self.path_utils.relative_to_working_out_include_env(hpp_path)
        Path(cpp_path.parent).mkdir(parents=True, exist_ok=True)
        cpp_file = open(cpp_path, 'w')
        cpp_file.write('#include "' + str(own_include).replace('\\', '/') + '"' + '\n')
        cpp_file.close()

    def gen_enums(self):
        hpp_file = open(self.include_path, 'a')
        for enum in self.serializable_enums:
            enum.fill_header(hpp_file)
        hpp_file.close()

        cpp_file = open(self.cpp_path, 'a')
        for enum in self.serializable_enums:
            enum.fill_source(cpp_file)
        cpp_file.close()

    def gen_classes(self):
        hpp_file = open(self.include_path, 'a')
        for _class in self.serializable_classes:
            _class.fill_header(hpp_file)
        hpp_file.close()

        cpp_file = open(self.cpp_path, 'a')
        for _class in self.serializable_classes:
            _class.fill_source(cpp_file, self.path_utils)
        cpp_file.close()


class Generator:
    def __init__(self, path_utils):
        self.path_utils = path_utils
        self.files = path_utils.get_path_list()
        self.enums = []
        self.classes = []

    def analyze_sources(self):
        for path in self.files:
            print('Analysis file ' + str(path))
            index = clang.cindex.Index.create()
            arg_list = ['-std=c++17', '-I' + str(self.path_utils.working_env_in_path)]
            for add_include in self.path_utils.add_includes:
                add_include_path = PurePath(add_include)
                arg_list.append('-I' + str(add_include_path))
            options = clang.cindex.TranslationUnit.PARSE_INCOMPLETE \
                | clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES\
                | clang.cindex.TranslationUnit.PARSE_PRECOMPILED_PREAMBLE
            translation_unit = index.parse(str(path), args=arg_list, options=options)
            self.analyze_unit(translation_unit.cursor)

        for _class in self.classes:
            dependencies = self.get_all_dependencies(_class)
            _class.init_dependencies(dependencies)
            for base in _class.bases:
                serializable_bases = self.get_all_serializable_bases(base.full_type_name)
                base.init_classes(serializable_bases)

    def analyze_unit(self, root: clang.cindex.Cursor):
        for child in root.get_children():
            current_filename = child.translation_unit.spelling
            if child.location.file.name != current_filename:
                continue

            if child.kind == clang.cindex.CursorKind.NAMESPACE:
                self.analyze_unit(child)
                continue

            if not TagUtils.has_tag(child, 'serializable'):
                continue

            if child.kind == clang.cindex.CursorKind.ENUM_DECL:
                self.add_enum(child)

            if child.kind in [clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL]:
                self.add_class(child)

    def add_enum(self, node: clang.cindex.Cursor):
        new_enum = SerializableEnum(node)
        self.enums.append(new_enum)

    def add_class(self, node: clang.cindex.Cursor):
        new_class = SerializableClassFactory.CreateClass(node)
        self.classes.append(new_class)

    def generate(self):
        print('Gathering generation info...')
        generate_units = self.get_generate_info(self.files)

        print('Preparing files...')
        self.path_utils.rm_out_dirs()
        for generate_unit in generate_units:
            generate_unit.prepare_files()

        print('Filling enums...')
        for generate_unit in generate_units:
            generate_unit.gen_enums()
        print('Filling classes...')
        for generate_unit in generate_units:
            generate_unit.gen_classes()

    def get_generate_info(self, files):
        generate_units = []
        print('Sorting classes...')
        sorted_classes = self.get_sorted_classes()
        for filename in files:
            print('Gathering generation info for ' + str(filename))
            new_unit = GenerateUnit(filename, self.path_utils, self.enums, sorted_classes)
            if new_unit.is_valid():
                generate_units.append(new_unit)
        return generate_units

    def get_sorted_classes(self):
        result = []

        for _class in self.classes:
            if not self.get_only_serializable_bases(_class):
                result.append(_class)

        while len(result) != len(self.classes):
            temp_classes = []
            for _class in self.classes:
                if result.count(_class) > 0:
                    continue

                if Generator.consist_base_classes(result, self.get_only_serializable_bases(_class)):
                    temp_classes.append(_class)

            for temp_class in temp_classes:
                result.append(temp_class)

        result.reverse()
        return result

    @staticmethod
    def consist_base_classes(class_list, base_classes):
        for _class in class_list:
            for base_class in base_classes:
                if _class.full_type_name == base_class.full_type_name:
                    return True
        return False

    def get_only_serializable_bases(self, _class):
        bases = []
        for base in _class.bases:
            base_class = self.get_class(base.full_type_name)
            if base_class:
                bases.append(base)
        return bases

    def get_all_dependencies(self, _class):
        dependencies = []
        for base in _class.get_all_serializable_bases():
            base_class = self.get_class(base.full_type_name)
            if base_class:
                dependency = Dependency(base_class.filename)
                dependencies.append(dependency)

        for _property in _class.properties:
            property_class = self.get_class(_property.full_type_name)
            if property_class:
                dependency = Dependency(property_class.filename)
                dependencies.append(dependency)
            property_enum = self.get_enum(_property.full_type_name)
            if property_enum:
                dependency = Dependency(property_enum.filename)
                dependencies.append(dependency)

        for method in _class.methods:
            method_class = self.get_class(method.full_type_name)
            if method_class:
                dependency = Dependency(method_class.filename)
                dependencies.append(dependency)
            method_enum = self.get_enum(method.full_type_name)
            if method_enum:
                dependency = Dependency(method_enum.filename)
                dependencies.append(dependency)

        return dependencies

    def get_class(self, full_type_name):
        clean_type_name = TypeUtils.clean_up(full_type_name)
        for _class in self.classes:
            if clean_type_name == _class.full_type_name:
                return _class
        return None

    def get_all_serializable_bases(self, full_type_name):
        all_bases = []
        base_class = self.get_class(full_type_name)
        if base_class:
            all_bases.append(base_class)
            for base_base in base_class.bases:
                base_bases = self.get_all_serializable_bases(base_base.full_type_name)
                for base_base_class in base_bases:
                    if all_bases.count(base_base_class) == 0:
                        all_bases.append(base_base_class)
        return all_bases

    def get_enum(self, full_type_name):
        clean_type_name = TypeUtils.clean_up(full_type_name)
        for enum in self.enums:
            if clean_type_name == enum.full_type_name:
                return enum
        return None
