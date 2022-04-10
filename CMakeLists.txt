cmake_minimum_required (VERSION 3.12)

project ("MegaQuest")

if (WIN32)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
endif()

set(BUILD_SHARED_LIBS on)

add_subdirectory ("MegaQuestGameplay")
add_subdirectory ("MegaQuestConsole")
