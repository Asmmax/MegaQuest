cmake_minimum_required (VERSION 3.12)

set(console_include_dir "include/")
set(console_src_dir "src/")

if (WIN32)
	message (STATUS "Generating containers for QuestCore")
	get_target_property(in_paths QuestCore INCLUDE_DIRECTORIES)
	list(GET in_paths 0 in_path)
	set(gen_dir ".generated/QuestCore")
	set(out_include_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
	set(out_source_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_src_dir}")
	execute_process(
		COMMAND cmd /C set out_include_dir=${gen_dir} && set out_source_dir=${gen_dir} && call scripts/win/generate_containers.bat ${in_path} ${out_include_path} ${out_source_path}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)

	message (STATUS "Generating containers for Current")
	get_target_property(add_includes QuestCore INCLUDE_DIRECTORIES)
	list(GET add_includes 0 add_include)
	set(in_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
	set(gen_dir ".generated/Current")
	set(out_include_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
	set(out_source_path "${CMAKE_CURRENT_SOURCE_DIR}/${console_src_dir}")
	execute_process(
		COMMAND cmd /C set out_include_dir=${gen_dir} && set out_source_dir=${gen_dir} && set add_includes=${add_include} && call scripts/win/generate_containers.bat ${in_path} ${out_include_path} ${out_source_path}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()

file(GLOB_RECURSE console_include CONFIGURE_DEPENDS "${console_include_dir}/*.hpp")
file(GLOB_RECURSE console_src CONFIGURE_DEPENDS "${console_src_dir}/*.cpp")

add_executable (MegaQuestConsole 
${console_include}
${console_src})

target_compile_features (MegaQuestConsole PRIVATE cxx_std_17)
set_target_properties(MegaQuestConsole PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MegaQuestConsole PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${console_include_dir}")
target_link_libraries(MegaQuestConsole PRIVATE QuestCore PRIVATE json)
add_dependencies(MegaQuestConsole QuestCore)

set(RESOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json)
