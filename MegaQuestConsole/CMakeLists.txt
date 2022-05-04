cmake_minimum_required (VERSION 3.12)

set(console_include_dir "include/")
set(console_src_dir "src/")

file(GLOB_RECURSE console_include CONFIGURE_DEPENDS "${console_include_dir}/*.hpp")
file(GLOB_RECURSE console_src CONFIGURE_DEPENDS "${console_src_dir}/*.cpp")

add_executable (MegaQuestConsole 
${console_include}
${console_src})

target_compile_features (MegaQuestConsole PRIVATE cxx_std_17)
set_target_properties(MegaQuestConsole PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MegaQuestConsole PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
target_link_libraries(MegaQuestConsole PRIVATE QuestCore PRIVATE json)

set(RESOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json)
