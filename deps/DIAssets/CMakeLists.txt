add_library(DIAssets INTERFACE)

target_include_directories(DIAssets INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(DIAssets INTERFACE json)
