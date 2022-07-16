from pathlib import Path
from pathlib import PurePath
import clang.cindex
from string import Template
import argparse

enums = []
classes = []
inherited_tags = ['shared', 'polymorphic']

parser = argparse.ArgumentParser(description="Generator",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("in_path", help="Input working environment")
parser.add_argument("out_include_path", help="Output include working environment")
parser.add_argument("out_source_path", help="Output source working environment")
parser.add_argument("--in_dir", help="Input directory")
parser.add_argument("--out_include_dir", help="Output include directory")
parser.add_argument("--out_source_dir", help="Output source directory")
args = parser.parse_args()

working_env_in_path = args.in_path
working_env_out_include_path = args.out_include_path
working_env_out_source_path = args.out_source_path

in_dir = ''
if args.in_dir:
    in_dir = args.in_dir

out_include_dir = ''
if args.out_include_dir:
    out_include_dir = args.out_include_dir

out_source_dir = ''
if args.out_source_dir:
    out_source_dir = args.out_source_dir

in_path = PurePath(working_env_in_path).joinpath(in_dir)
out_include_path = PurePath(working_env_out_include_path).joinpath(out_include_dir)
out_source_path = PurePath(working_env_out_source_path).joinpath(out_source_dir)

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
polymorphic_bind_decl_tpl_path = 'templates/Polymorphic/bind_decl.tpl'
polymorphic_bind_def_tpl_path = 'templates/Polymorphic/bind_def.tpl'
polymorphic_bind_using_tpl_path = 'templates/Polymorphic/bind_using.tpl'

shared_interface_decl_tpl_path = 'templates/Shared/interface_decl.tpl'
shared_interface_def_tpl_path = 'templates/Shared/interface_def.tpl'
shared_impl_decl_tpl_path = 'templates/Shared/impl_decl.tpl'
shared_impl_def_tpl_path = 'templates/Shared/impl_def.tpl'
shared_method_tpl_path = 'templates/Shared/method.tpl'
shared_bind_decl_tpl_path = 'templates/Shared/bind_decl.tpl'
shared_bind_def_tpl_path = 'templates/Shared/bind_def.tpl'
shared_bind_using_tpl_path = 'templates/Shared/bind_using.tpl'


class SerializableEnum:
    filename = ''
    full_type_name = ''
    elements = []


class Tag:
    name = ''
    args = []


class Base:
    full_type_name = ''


class Child:
    filename = ''
    type_name = ''
    full_type_name = ''


class Property:
    arg_name = ''
    full_type_name = ''


class Method:
    name = ''
    arg_name = ''
    full_type_name = ''


class SerializableClass:
    filename = ''
    type_name = ''
    full_type_name = ''
    tags = []
    bases = []
    children = []
    properties = []
    methods = []


class GenerateUnit:
    origin_path = ''
    include_path = ''
    cpp_path = ''
    serializable_enums = []
    serializable_classes = []


def has_tag(node, tag_name):
    comment = node.raw_comment
    tags = []
    if comment:
        tags = comment.split()

    return tags.count('@' + tag_name) > 0


def consist_tag(tags, tag_name):
    for tag in tags:
        if tag.name == tag_name:
            return True
    return False


def remove_tag(tags, tag_name):
    remove_list = []
    for tag in tags:
        if tag.name == tag_name:
            remove_list.append(tag)
    for removed_tag in remove_list:
        tags.remove(removed_tag)


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


def get_inherited_tags(node):
    for child in node.get_children():
        if child.kind != clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
            continue

        base = child.type.get_declaration().get_definition()
        tags = get_inherited_tags(base)
        base_tags = parse_tags(base.raw_comment)
        for base_tag in base_tags:
            if base_tag.name in inherited_tags:
                if not consist_tag(tags, base_tag.name):
                    tags.append(base_tag)
        return tags
    return []


def find_bases(node):
    bases = []
    for child in node.get_children():
        if child.kind != clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
            continue

        base = child.type.get_declaration()
        new_base = Base()
        new_base.full_type_name = base.type.spelling
        bases.append(new_base)
    return bases


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
        if has_tag(child, 'inject'):
            return child

    return suit_children[0]


def get_pure_type_name(node):
    type_name = node.type.get_canonical().spelling.replace('&', '').strip()

    type_name = type_name.replace('const', '', 1).strip()

    return type_name.replace('std::weak_ptr', 'std::shared_ptr', 1).strip()


def find_properties(node):
    properties = []
    constructor = get_suit_constructor(node)
    args = []
    if constructor:
        args = constructor.get_arguments()
    else:
        args = node.type.get_fields()

    for arg in args:
        if arg.access_specifier in [clang.cindex.AccessSpecifier.PRIVATE, clang.cindex.AccessSpecifier.PROTECTED]:
            continue
        new_prop = Property()
        new_prop.arg_name = arg.spelling
        new_prop.full_type_name = get_pure_type_name(arg)
        properties.append(new_prop)
    return properties


def get_methods(node):
    methods = []
    for child in node.get_children():
        if child.kind == clang.cindex.CursorKind.CXX_METHOD:
            if has_tag(child, 'inject'):
                methods.append(child)
    return methods


def find_methods(node):
    methods = []
    for method in get_methods(node):
        new_method = Method()
        new_method.name = method.spelling

        args = method.get_arguments()
        for arg in args:
            new_method.arg_name = arg.spelling
            new_method.full_type_name = get_pure_type_name(arg)
            break

        methods.append(new_method)
    return methods


def add_enum(node: clang.cindex.Cursor):
    new_enum = SerializableEnum()
    new_enum.filename = node.translation_unit.spelling
    new_enum.full_type_name = node.type.spelling
    new_enum.elements = []
    for elem in node.get_children():
        new_enum.elements.append(elem.spelling)
    enums.append(new_enum)


def add_class(node: clang.cindex.Cursor):
    new_class = SerializableClass()
    new_class.filename = node.translation_unit.spelling
    new_class.type_name = node.spelling
    new_class.full_type_name = node.type.spelling

    new_class.tags = parse_tags(node.raw_comment)
    base_tags = get_inherited_tags(node)
    for base_tag in base_tags:
        remove_tag(new_class.tags, base_tag.name)
        new_class.tags.append(base_tag)

    new_class.bases = find_bases(node)
    new_class.properties = find_properties(node)
    new_class.methods = find_methods(node)
    classes.append(new_class)


def analyze_unit(root: clang.cindex.Cursor):
    for child in root.get_children():
        current_filename = child.translation_unit.spelling
        if child.location.file.name != current_filename:
            continue

        if child.kind == clang.cindex.CursorKind.NAMESPACE:
            analyze_unit(child)
            continue

        if not has_tag(child, 'serializable'):
            continue

        if child.kind == clang.cindex.CursorKind.ENUM_DECL:
            add_enum(child)

        if child.kind in [clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL]:
            add_class(child)


def get_gen_path_for(path):
    raw_path = PurePath(path).relative_to(in_path).with_suffix('')
    filename = raw_path.name
    return raw_path.with_name(filename + '_gen')


def compute_children():
    for _class in classes:
        _class.children = []
        for child_class in classes:
            for base_class in child_class.bases:
                if base_class.full_type_name == _class.full_type_name:
                    new_child = Child()
                    new_child.filename = child_class.filename
                    new_child.type_name = child_class.type_name
                    new_child.full_type_name = child_class.full_type_name
                    _class.children.append(new_child)


def open_or_create(filename):
    try:
        return open(filename, 'r')
    except IOError:
        return open(filename, 'w')
    return None


def rm_tree(pth):
    pth = Path(pth)
    if not pth.exists():
        return
    for child in pth.glob('*'):
        if child.is_file():
            child.unlink()
        else:
            rm_tree(child)
    pth.rmdir()


def prepare_header_file(in_path, hpp_path):
    in_include = PurePath(in_path).relative_to(working_env_in_path)
    Path(hpp_path.parent).mkdir(parents=True, exist_ok=True)
    hpp_file = open(hpp_path, 'w')
    hpp_file.write('#pragma once\n')
    hpp_file.write('#include "' + str(in_include).replace('\\', '/') + '"' + '\n')
    hpp_file.close()


def prepare_source_file(hpp_path, cpp_path):
    own_include = PurePath(hpp_path).relative_to(working_env_out_include_path)
    Path(cpp_path.parent).mkdir(parents=True, exist_ok=True)
    cpp_file = open(cpp_path, 'w')
    cpp_file.write('#include "' + str(own_include).replace('\\', '/') + '"' + '\n')
    cpp_file.close()


enum_hpp_tpl = Template(Path(enum_decl_tpl_path).read_text())


def fill_enum_header(enum, stream):
    enum_full_type = enum.full_type_name
    stream.write(enum_hpp_tpl.substitute(locals()))


enum_cpp_tpl = Template(Path(enum_def_tpl_path).read_text())
enum_value_cpp_tpl = Template(Path(enum_value_tpl_path).read_text())


def fill_enum_source(enum, stream):
    enum_values_list = []
    enum_full_type = enum.full_type_name
    for enum_value_name in enum.elements:
        enum_value = enum_value_cpp_tpl.substitute(locals())
        enum_values_list.append(enum_value)
    enum_values = ',\n'.join(enum_values_list)
    stream.write(enum_cpp_tpl.substitute(locals()))


property_cpp_tpl = Template(Path(property_tpl_path).read_text())
bindImpl_hpp_tpl = Template(Path(polymorphic_bind_decl_tpl_path).read_text())
bindImpl_cpp_tpl = Template(Path(polymorphic_bind_def_tpl_path).read_text())
impl_hpp_tpl = Template(Path(impl_tpl_path).read_text())
factoryBinderImpl_cpp_tpl = Template(Path(polymorphic_bind_using_tpl_path).read_text())


shared_impl_hpp_tpl = Template(Path(shared_impl_decl_tpl_path).read_text())


def fill_shared_impl_header(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    method_arg_types_list = []
    for method in _class.methods:
        method_arg_types_list.append(', ' + method.full_type_name)
    method_arg_types = '\n'.join(method_arg_types_list)

    property_types_list = []
    for property in _class.properties:
        property_types_list.append(', ' + property.full_type_name)
    property_types = '\n'.join(property_types_list)

    stream.write(shared_impl_hpp_tpl.substitute(locals()))


method_cpp_tpl = Template(Path(shared_method_tpl_path).read_text())
shared_impl_cpp_tpl = Template(Path(shared_impl_def_tpl_path).read_text())
containerBinderImpl_cpp_tpl = Template(Path(shared_bind_using_tpl_path).read_text())


def fill_shared_impl_source(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    method_list = []
    for method in _class.methods:
        full_arg_type_name = method.full_type_name
        arg_name = method.arg_name
        method_name = method.name
        simple_method = method_cpp_tpl.substitute(locals())
        method_list.append(simple_method)
    methods = ',\n'.join(method_list)

    property_list = []
    for property in _class.properties:
        full_arg_type_name = property.full_type_name
        arg_name = property.arg_name
        simple_property = property_cpp_tpl.substitute(locals())
        property_list.append(', ' + simple_property)
    properties = '\n'.join(property_list)

    base_list = []
    for base in _class.bases:
        full_base_type_name = base.full_type_name
        container_binder_impl = containerBinderImpl_cpp_tpl.substitute(locals())
        base_list.append(container_binder_impl)
    container_binder_impls = '\n'.join(base_list)

    stream.write(shared_impl_cpp_tpl.substitute(locals()))


shared_interface_hpp_tpl = Template(Path(shared_interface_decl_tpl_path).read_text())
bindImpl_shared_hpp_tpl = Template(Path(shared_bind_decl_tpl_path).read_text())


def fill_shared_interface_header(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    child_include_list = []
    for child in _class.children:
        if PurePath(child.filename) == PurePath(_class.filename):
            continue
        gen_path = PurePath(out_include_dir).joinpath(get_gen_path_for(child.filename)).with_suffix('.hpp')
        child_include = '#include ' + '"' + str(gen_path).replace('\\', '/') + '"'
        if child_include_list.count(child_include) == 0:
            child_include_list.append(child_include)
    children_include = '\n'.join(child_include_list)

    impl_name_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        impl_name_list.append(', ' + impl_hpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        impl_name_list.append(', ' + impl_hpp_tpl.substitute(locals()))
    impl_names = '\n'.join(impl_name_list)

    bind_impl_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        bind_impl_list.append(bindImpl_shared_hpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        bind_impl_list.append(bindImpl_shared_hpp_tpl.substitute(locals()))
    bind_impls = '\n'.join(bind_impl_list)

    stream.write(shared_interface_hpp_tpl.substitute(locals()))


shared_interface_cpp_tpl = Template(Path(shared_interface_def_tpl_path).read_text())
bindImpl_shared_cpp_tpl = Template(Path(shared_bind_def_tpl_path).read_text())


def fill_shared_interface_source(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    bind_impl_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        bind_impl_list.append(bindImpl_shared_cpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        bind_impl_list.append(bindImpl_shared_cpp_tpl.substitute(locals()))
    bind_impls = '\n'.join(bind_impl_list)

    shared_name = ''
    for tag in _class.tags:
        if tag.name == 'shared':
            shared_name = tag.args[0]

    stream.write(shared_interface_cpp_tpl.substitute(locals()))


polymorphic_impl_hpp_tpl = Template(Path(polymorphic_impl_decl_tpl_path).read_text())


def fill_polymorphic_impl_header(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    property_types_list = []
    for property in _class.properties:
        property_types_list.append(', ' + property.full_type_name)
    property_types = '\n'.join(property_types_list)

    stream.write(polymorphic_impl_hpp_tpl.substitute(locals()))


polymorphic_impl_cpp_tpl = Template(Path(polymorphic_impl_def_tpl_path).read_text())


def fill_polymorphic_impl_source(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    property_list = []
    for property in _class.properties:
        full_arg_type_name = property.full_type_name
        arg_name = property.arg_name
        simple_property = property_cpp_tpl.substitute(locals())
        property_list.append(simple_property)
    properties = ',\n'.join(property_list)

    base_list = []
    for base in _class.bases:
        full_base_type_name = base.full_type_name
        factory_binder_impl = factoryBinderImpl_cpp_tpl.substitute(locals())
        base_list.append(factory_binder_impl)
    factory_binder_impls = '\n'.join(base_list)

    stream.write(polymorphic_impl_cpp_tpl.substitute(locals()))


polymorphic_interface_hpp_tpl = Template(Path(polymorphic_interface_decl_tpl_path).read_text())


def fill_polymorphic_interface_header(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    child_include_list = []
    for child in _class.children:
        if PurePath(child.filename) == PurePath(_class.filename):
            continue
        gen_path = PurePath(out_include_dir).joinpath(get_gen_path_for(child.filename)).with_suffix('.hpp')
        child_include = '#include ' + '"' + str(gen_path).replace('\\', '/') + '"'
        if child_include_list.count(child_include) == 0:
            child_include_list.append(child_include)
    children_include = '\n'.join(child_include_list)

    impl_name_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        impl_name_list.append(', ' + impl_hpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        impl_name_list.append(', ' + impl_hpp_tpl.substitute(locals()))
    impl_names = '\n'.join(impl_name_list)

    bind_impl_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        bind_impl_list.append(bindImpl_hpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        bind_impl_list.append(bindImpl_hpp_tpl.substitute(locals()))
    bind_impls = '\n'.join(bind_impl_list)

    stream.write(polymorphic_interface_hpp_tpl.substitute(locals()))


polymorphic_interface_cpp_tpl = Template(Path(polymorphic_interface_def_tpl_path).read_text())


def fill_polymorphic_interface_source(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    bind_impl_list = []
    if not consist_tag(_class.tags, 'abstract'):
        impl_type_name = _class.type_name
        bind_impl_list.append(bindImpl_cpp_tpl.substitute(locals()))
    for child in _class.children:
        impl_type_name = child.type_name
        bind_impl_list.append(bindImpl_cpp_tpl.substitute(locals()))
    bind_impls = '\n'.join(bind_impl_list)

    stream.write(polymorphic_interface_cpp_tpl.substitute(locals()))


simple_hpp_tpl = Template(Path(simple_decl_tpl_path).read_text())


def fill_simple_header(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    property_types_list = []
    for property in _class.properties:
        property_types_list.append(', ' + property.full_type_name)
    property_types = '\n'.join(property_types_list)

    stream.write(simple_hpp_tpl.substitute(locals()))


simple_cpp_tpl = Template(Path(simple_def_tpl_path).read_text())


def fill_simple_source(_class, stream):
    type_name = _class.type_name
    full_type_name = _class.full_type_name

    property_list = []
    for property in _class.properties:
        full_arg_type_name = property.full_type_name
        arg_name = property.arg_name
        simple_property = property_cpp_tpl.substitute(locals())
        property_list.append(simple_property)
    properties = ',\n'.join(property_list)

    stream.write(simple_cpp_tpl.substitute(locals()))


def gen_enums(generate_units):
    for generate_unit in generate_units:
        hpp_file = open(generate_unit.include_path, 'a')
        for enum in generate_unit.serializable_enums:
            fill_enum_header(enum, hpp_file)
        hpp_file.close()

        cpp_file = open(generate_unit.cpp_path, 'a')
        for enum in generate_unit.serializable_enums:
            fill_enum_source(enum, cpp_file)
        cpp_file.close()


def gen_clases(generate_units):
    for generate_unit in generate_units:
        hpp_file = open(generate_unit.include_path, 'a')
        for _class in generate_unit.serializable_classes:
            if consist_tag(_class.tags, 'shared'):
                if not consist_tag(_class.tags, 'abstract'):
                    fill_shared_impl_header(_class, hpp_file)
                fill_shared_interface_header(_class, hpp_file)
            elif consist_tag(_class.tags, 'polymorphic'):
                if not consist_tag(_class.tags, 'abstract'):
                    fill_polymorphic_impl_header(_class, hpp_file)
                fill_polymorphic_interface_header(_class, hpp_file)
            else:
                fill_simple_header(_class, hpp_file)
        hpp_file.close()

        cpp_file = open(generate_unit.cpp_path, 'a')
        for _class in generate_unit.serializable_classes:
            if consist_tag(_class.tags, 'shared'):
                if not consist_tag(_class.tags, 'abstract'):
                    fill_shared_impl_source(_class, cpp_file)
                fill_shared_interface_source(_class, cpp_file)
            elif consist_tag(_class.tags, 'polymorphic'):
                if not consist_tag(_class.tags, 'abstract'):
                    fill_polymorphic_impl_source(_class, cpp_file)
                fill_polymorphic_interface_source(_class, cpp_file)
            else:
                fill_simple_source(_class, cpp_file)
        cpp_file.close()


def analyze_sources(files):
    for path in files:
        index = clang.cindex.Index.create()
        translation_unit = index.parse(str(path), args=['-std=c++17', '-I' + str(working_env_in_path)])
        analyze_unit(translation_unit.cursor)
    compute_children()


def consist_base_classes(class_list, base_classes):
    for _class in class_list:
        for base_class in base_classes:
            if _class.full_type_name == base_class.full_type_name:
                return True
    return False


def get_sorted_classes():
    result = []

    for _class in classes:
        if not _class.bases:
            result.append(_class)

    while len(result) != len(classes):
        temp_classes = []
        for _class in classes:
            if result.count(_class) > 0:
                continue

            if consist_base_classes(result, _class.bases):
                temp_classes.append(_class)

        for temp_class in temp_classes:
            result.append(temp_class)

    result.reverse()
    return result


def get_generate_info(files):
    generate_units = []
    sorted_classs = get_sorted_classes()
    for filename in files:
        new_unit = GenerateUnit()
        new_unit.origin_path = PurePath(filename)
        new_unit.include_path = PurePath(out_include_path).joinpath(get_gen_path_for(filename)).with_suffix('.hpp')
        new_unit.cpp_path = PurePath(out_source_path).joinpath(get_gen_path_for(filename)).with_suffix('.cpp')

        new_unit.serializable_enums = []
        for enum in enums:
            if PurePath(enum.filename) == PurePath(filename):
                new_unit.serializable_enums.append(enum)

        new_unit.serializable_classes = []
        for sorted_class in sorted_classs:
            if PurePath(sorted_class.filename) == PurePath(filename):
                new_unit.serializable_classes.append(sorted_class)

        if new_unit.serializable_enums or new_unit.serializable_classes:
            generate_units.append(new_unit)
    return generate_units


def prepare_files(generate_units):
    for generate_unit in generate_units:
        prepare_header_file(generate_unit.origin_path, generate_unit.include_path)
        prepare_source_file(generate_unit.include_path, generate_unit.cpp_path)


def generate(files):
    generate_units = get_generate_info(files)

    rm_tree(out_include_path)
    rm_tree(out_source_path)
    prepare_files(generate_units)

    gen_enums(generate_units)
    gen_clases(generate_units)


pathList = sorted(Path(in_path).rglob('*.hpp'))
print('Analysis of input files...')
analyze_sources(pathList)
print('Generate files...')
generate(pathList)
print('Generating successed!')
