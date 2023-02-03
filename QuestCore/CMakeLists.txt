cmake_minimum_required (VERSION 3.12)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(quest_include_dir "include/")
set(quest_src_dir "src/")
set(out_include_path "${PROJECT_BINARY_DIR}/.generated/QuestCore/${quest_include_dir}")
set(out_source_path "${PROJECT_BINARY_DIR}/.generated/QuestCore/${quest_src_dir}")
set(cache_path "${PROJECT_BINARY_DIR}/.generated/QuestCore")
set(scripts_dir "${PROJECT_SOURCE_DIR}/scripts")

if (WIN32)
	message (STATUS "Generating containers for QuestCore")
	set(in_path "${CMAKE_CURRENT_SOURCE_DIR}/${quest_include_dir}")
	set(gen_dir "QuestCore")
	execute_process(
		COMMAND cmd /C set out_include_dir=${gen_dir} && set out_source_dir=${gen_dir} && set cache_path=${cache_path} && call "${scripts_dir}/win/generate_containers.bat" ${in_path} ${out_include_path} ${out_source_path}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()

file(GLOB_RECURSE quest_include CONFIGURE_DEPENDS "${quest_include_dir}/*.hpp")
file(GLOB_RECURSE quest_src "${quest_src_dir}/*.cpp")

add_library (QuestCore SHARED 
${quest_include}  
${quest_src})

target_compile_features (QuestCore PRIVATE cxx_std_17)
set_target_properties(QuestCore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(QuestCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${quest_include_dir}")

install(TARGETS QuestCore LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${quest_include} TYPE INCLUDE DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
