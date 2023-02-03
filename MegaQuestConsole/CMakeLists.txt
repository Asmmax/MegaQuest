cmake_minimum_required (VERSION 3.12)

set(console_include_dir "include/")
set(console_src_dir "src/")
set(out_include_path "${PROJECT_BINARY_DIR}/.generated/MegaQuestConsole/${console_include_dir}")
set(out_source_path "${PROJECT_BINARY_DIR}/.generated/MegaQuestConsole/${console_src_dir}")
set(cache_path "${PROJECT_BINARY_DIR}/.generated/MegaQuestConsole")
set(scripts_dir "${PROJECT_SOURCE_DIR}/scripts")

if (WIN32)
	message (STATUS "Generating containers for Current")
	get_target_property(add_includes QuestCore INCLUDE_DIRECTORIES)
	list(GET add_includes 0 add_include)
	set(in_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
	set(gen_dir "MegaQuestConsole")
	execute_process(
		COMMAND cmd /C set out_include_dir=${gen_dir} && set out_source_dir=${gen_dir} && set add_includes=${add_include} && set cache_path=${cache_path} && call "${scripts_dir}/win/generate_containers.bat" ${in_path} ${out_include_path} ${out_source_path}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()

file(GLOB_RECURSE console_include CONFIGURE_DEPENDS "${console_include_dir}/*.hpp")
file(GLOB_RECURSE console_src "${console_src_dir}/*.cpp")

set(core_out_include_path "${PROJECT_BINARY_DIR}/.generated/QuestCore/${console_include_dir}")
set(core_out_source_path "${PROJECT_BINARY_DIR}/.generated/QuestCore/${console_src_dir}")

file(GLOB_RECURSE gen_include 
"${out_include_path}/*.hpp" 
"${core_out_include_path}/*.hpp")

file(GLOB_RECURSE gen_src 
"${out_source_path}/*.cpp" 
"${core_out_source_path}/*.cpp")

add_executable (MegaQuestConsole 
${console_include}
${console_src}
${gen_include}
${gen_src})

target_compile_features (MegaQuestConsole PRIVATE cxx_std_17)
set_target_properties(MegaQuestConsole PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MegaQuestConsole 
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}"
PRIVATE "${out_include_path}"
PRIVATE "${core_out_include_path}")
target_link_libraries(MegaQuestConsole PRIVATE QuestCore PRIVATE DIAssets)
add_dependencies(MegaQuestConsole QuestCore)

set(RESOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json)
