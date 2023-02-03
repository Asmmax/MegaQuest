import argparse
from analyzer import CachedAnalyzer
from analyzer import ClassesConverter
from generator import Generator
from generator import DirEnvironment


parser = argparse.ArgumentParser(description="Generator",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("in_path", help="Input working environment")
parser.add_argument("out_include_path", help="Output include working environment")
parser.add_argument("out_source_path", help="Output source working environment")
parser.add_argument("--in_dir", help="Input directory")
parser.add_argument("--out_include_dir", help="Output include directory")
parser.add_argument("--out_source_dir", help="Output source directory")
parser.add_argument("--add_includes", help="Additional include paths")
parser.add_argument("--cache_path", help="Cache path")
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

cache_path = ''
if args.cache_path:
    cache_path = args.cache_path

add_includes = []
if args.add_includes:
    add_includes = args.add_includes.split(';')

path_utils = DirEnvironment(working_env_in_path, working_env_out_include_path, working_env_out_source_path,
                            in_dir, out_include_dir, out_source_dir, cache_path, add_includes)

analyzer = CachedAnalyzer(path_utils)
classes_converter = ClassesConverter(analyzer)

generator = Generator(path_utils, classes_converter)
print('Generate files...')
generator.generate()
print('Generating success!')