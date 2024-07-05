cmake_minimum_required (VERSION 3.8)

set(assets_dir "${CMAKE_CURRENT_SOURCE_DIR}/assets")

generate_di_files(TARGET MegaQuestConsole DEPS QuestCore WITH_REGISTER WITH_META)

file(GLOB_RECURSE cur_include "${DI_CURRENT_INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE cur_src "${DI_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB_RECURSE gen_include "${DI_CURRENT_OUT_INCLUDE_PATH}/*.hpp")
file(GLOB_RECURSE gen_src "${DI_CURRENT_OUT_SOURCE_PATH}/*.cpp")

add_executable (MegaQuestConsole 
${cur_include}
${cur_src}
${gen_include}
${gen_src})

target_compile_features (MegaQuestConsole PRIVATE cxx_std_17)
target_include_directories(MegaQuestConsole 
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
PRIVATE "${DI_CURRENT_OUT_INCLUDE_PATH}")

target_link_libraries(MegaQuestConsole PRIVATE QuestCore)
setup_di_cache(TARGET MegaQuestConsole)

file(RELATIVE_PATH RESOURCE_PATH ${PROJECT_BINARY_DIR} ${assets_dir})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.dat.in ${PROJECT_BINARY_DIR}/settings.dat)
