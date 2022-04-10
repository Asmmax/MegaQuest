cmake_minimum_required (VERSION 3.12)

set(console_include_dir "include/")
set(console_src_dir "src/")

set(console_include 
"MegaQuestGameplay.hpp")

set(console_src 
"MegaQuestGameplay.cpp")

list(TRANSFORM console_include PREPEND ${console_include_dir})
list(TRANSFORM console_src PREPEND ${console_src_dir})

add_executable (MegaQuestConsole 
${console_include}
${console_src})

target_compile_features (MegaQuestConsole PRIVATE cxx_std_17)
set_target_properties(MegaQuestConsole PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MegaQuestConsole PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")