from pathlib import Path
from pathlib import PurePath
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


class SerializableEnum:
    def __init__(self, filename: str, full_type_name: str, elements: list[str]):
        self.filename = filename
        self.full_type_name = full_type_name
        self.elements = elements

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
    def __init__(self, full_type_name: str, is_serializable: bool, parents: list['Base']):
        self.full_type_name = full_type_name
        self.is_serializable = is_serializable
        self.parents = parents

    def get_all_serializable_parents(self):
        serializable_parents = []
        for parent in self.parents:
            if parent.is_serializable:
                serializable_parents.append(parent)
            parents_of_parent = parent.get_all_serializable_parents()
            serializable_parents.extend(parents_of_parent)
        return serializable_parents


class Property:
    def __init__(self, arg_name: str, full_type_name: str):
        self.arg_name = arg_name
        self.full_type_name = full_type_name


class Method:
    def __init__(self, method_name: str, args: list[Property]):
        self.name = method_name
        for arg in args:
            self.arg_name = arg.arg_name
            self.full_type_name = arg.full_type_name
            break


class Dependency:
    def __init__(self, filename: str):
        self.filename = filename


class SerializableClass:
    def __init__(self, filename: str, type_name: str, full_type_name: str,
                 bases: list[Base], properties: list[Property], methods: list[Method], dependencies: list[Dependency]):
        self.filename = filename
        self.type_name = type_name
        self.full_type_name = full_type_name
        self.bases = bases
        self.properties = properties
        self.methods = methods
        self.dependencies = dependencies

    def fill_header(self, stream):
        pass

    def fill_source(self, stream, path_utils):
        pass

    def get_all_serializable_bases(self):
        all_bases = []
        for base in self.bases:
            if base.is_serializable:
                all_bases.append(base)
            all_bases.extend(base.get_all_serializable_parents())
        return all_bases


class SharedInterface(SerializableClass):
    def __init__(self, filename, type_name, full_type_name, bases, properties, methods, dependencies):
        super(SharedInterface, self).__init__(filename, type_name, full_type_name, bases,
                                              properties, methods, dependencies)

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
    def __init__(self, filename, type_name, full_type_name, bases, properties, methods, dependencies, shared_name):
        self.shared_name = shared_name
        super(SharedClass, self).__init__(filename, type_name, full_type_name, bases,
                                          properties, methods, dependencies)

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
    def __init__(self, filename, type_name, full_type_name, bases, properties, methods, dependencies):
        super(PolymorphicInterface, self).__init__(filename, type_name, full_type_name, bases,
                                                   properties, methods, dependencies)

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
    def __init__(self, filename, type_name, full_type_name, bases, properties, methods, dependencies):
        super(PolymorphicClass, self).__init__(filename, type_name, full_type_name, bases,
                                               properties, methods, dependencies)

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
    def __init__(self, filename, type_name, full_type_name, bases, properties, methods, dependencies):
        super(SimpleClass, self).__init__(filename, type_name, full_type_name, bases,
                                          properties, methods, dependencies)

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


class GenerateUnit:
    def __init__(self, filename, path_utils, enums: list[SerializableEnum], classes: list[SerializableClass]):
        self.path_utils = path_utils
        self.origin_path = PurePath(filename)
        self.include_path = PurePath(path_utils.out_include_path).joinpath(
            path_utils.get_gen_path_for(filename)).with_suffix('.hpp')
        self.cpp_path = PurePath(path_utils.out_source_path).joinpath(
            path_utils.get_gen_path_for(filename)).with_suffix(
            '.cpp')
        self.serializable_enums = enums
        self.serializable_classes = classes

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


class ClassesGateway:
    def __init__(self):
        self.__enums = []
        self.__classes = []

    def read(self, files: list[Path]):
        self.__reset()
        self._init(files)
        self.__read_enums()
        self.__read_classes()

    def get_class(self, full_type_name: str):
        self.__read_unique_class(full_type_name)
        for _class in self.__classes:
            if full_type_name == _class.full_type_name:
                return _class
        return None

    def get_enum(self, full_type_name: str):
        self.__read_unique_enum(full_type_name)
        for enum in self.__enums:
            if full_type_name == enum.full_type_name:
                return enum
        return None

    def has_class(self, full_type_name: str):
        for _class in self.__classes:
            if full_type_name == _class.full_type_name:
                return True
        return False

    def has_enum(self, full_type_name: str):
        for enum in self.__enums:
            if full_type_name == enum.full_type_name:
                return True
        return False

    def get_enums(self):
        return self.__enums

    def get_classes(self):
        return self.__classes

    def _get_enums_names(self) -> list[str]:
        pass

    def _read_enum(self, enum_name: str):
        pass

    def _get_classes_names(self) -> list[str]:
        pass

    def _read_class(self, class_name: str):
        pass

    def _init(self, files: list[Path]):
        pass

    def _add_class(self, new_class: SerializableClass):
        self.__classes.append(new_class)

    def _add_enum(self, new_enum: SerializableEnum):
        self.__enums.append(new_enum)

    def __reset(self):
        self.__enums = []
        self.__classes = []

    def __read_enums(self):
        enums_names = self._get_enums_names()
        for enum_name in enums_names:
            self.__read_unique_enum(enum_name)

    def __read_unique_enum(self, enum_name: str):
        if self.has_enum(enum_name):
            return
        self._read_enum(enum_name)

    def __read_classes(self):
        classes_names = self._get_classes_names()
        for class_name in classes_names:
            self.__read_unique_class(class_name)

    def __read_unique_class(self, class_name: str):
        if self.has_class(class_name):
            return
        self._read_class(class_name)


class GenerateUnitGateway:
    def __init__(self, path_utils: PathUtils, classes_gateway: ClassesGateway):
        self.__path_utils = path_utils
        self.__classes_gateway = classes_gateway

    def get_generate_units(self, files: list[Path]) -> list[GenerateUnit]:
        print('Read files info...')
        self.__classes_gateway.read(files)
        enums = self.__classes_gateway.get_enums()
        classes = self.__classes_gateway.get_classes()
        return self.__get_generate_info(files, enums, classes)

    def __get_generate_info(self, files: list[Path], enums: list[SerializableEnum], classes: list[SerializableClass]):
        generate_units = []
        print('Sorting classes...')
        sorted_classes = GenerateUnitGateway.__sort_classes(classes)
        for filename in files:
            print('Gathering generation info for ' + str(filename))
            file_enums = GenerateUnitGateway.__filter_enums(filename, enums)
            file_classes = GenerateUnitGateway.__filter_classes(filename, sorted_classes)
            new_unit = GenerateUnit(filename, self.__path_utils, file_enums, file_classes)
            if new_unit.is_valid():
                generate_units.append(new_unit)
        return generate_units

    @staticmethod
    def __filter_enums(filename: Path, enums: list[SerializableEnum]) -> list[SerializableEnum]:
        filtered_enums = []
        for enum in enums:
            if PurePath(enum.filename) == PurePath(filename):
                filtered_enums.append(enum)
        return filtered_enums

    @staticmethod
    def __filter_classes(filename: Path, sorted_classes: list[SerializableClass]) -> list[SerializableClass]:
        filtered_classes = []
        for sorted_class in sorted_classes:
            if PurePath(sorted_class.filename) == PurePath(filename):
                filtered_classes.append(sorted_class)
        return filtered_classes

    @staticmethod
    def __sort_classes(classes: list[SerializableClass]):
        result = []

        for _class in classes:
            if not _class.get_all_serializable_bases():
                result.append(_class)

        while len(result) != len(classes):
            temp_classes = []
            for _class in classes:
                if result.count(_class) > 0:
                    continue

                if GenerateUnitGateway.__consist_base_classes(result, _class.get_all_serializable_bases()):
                    temp_classes.append(_class)

            for temp_class in temp_classes:
                result.append(temp_class)

        result.reverse()
        return result

    @staticmethod
    def __consist_base_classes(class_list, base_classes):
        for _class in class_list:
            for base_class in base_classes:
                if _class.full_type_name == base_class.full_type_name:
                    return True
        return False


class Generator:
    def __init__(self, path_utils: PathUtils, classes_gateway: ClassesGateway):
        self.__path_utils = path_utils
        self.__gateway = GenerateUnitGateway(path_utils, classes_gateway)

    def generate(self):
        print('Gathering generation info...')
        files = self.__path_utils.get_path_list()
        generate_units = self.__gateway.get_generate_units(files)

        print('Preparing files...')
        self.__path_utils.rm_out_dirs()
        for generate_unit in generate_units:
            generate_unit.prepare_files()

        print('Filling enums...')
        for generate_unit in generate_units:
            generate_unit.gen_enums()
        print('Filling classes...')
        for generate_unit in generate_units:
            generate_unit.gen_classes()
