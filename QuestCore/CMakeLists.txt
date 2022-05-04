cmake_minimum_required (VERSION 3.12)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(quest_include_dir "include/")
set(quest_src_dir "src/")

file(GLOB_RECURSE quest_include CONFIGURE_DEPENDS "${quest_include_dir}/*.hpp")
file(GLOB_RECURSE quest_src CONFIGURE_DEPENDS "${quest_src_dir}/*.cpp")

add_library (QuestCore SHARED 
${quest_include}  
${quest_src} "src/TextString.cpp")

target_compile_features (QuestCore PRIVATE cxx_std_17)
set_target_properties(QuestCore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(QuestCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${quest_include_dir}")

install(TARGETS QuestCore LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${quest_include} TYPE INCLUDE DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
