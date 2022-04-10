cmake_minimum_required (VERSION 3.12)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(quest_private_dir "include/private/")
set(quest_public_dir "include/public/")
set(quest_src_dir "src/")

set(quest_private_include 
)

set(quest_public_include 
)

set(quest_src 
)

list(TRANSFORM quest_private_include PREPEND ${quest_private_dir})
list(TRANSFORM quest_public_include PREPEND ${quest_public_dir})
list(TRANSFORM quest_src PREPEND ${quest_src_dir})

add_library (MegaQuestGameplay SHARED 
${quest_private_include}  
${quest_public_include} 
${simulations_src})

target_compile_features (MegaQuestGameplay PRIVATE cxx_std_17)
set_target_properties(MegaQuestGameplay PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(MegaQuestGameplay PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${quest_public_dir}")
target_include_directories(MegaQuestGameplay PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${quest_private_dir}")

install(TARGETS MegaQuestGameplay LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${quest_public_include} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
