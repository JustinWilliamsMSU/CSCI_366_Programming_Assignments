cmake_minimum_required(VERSION 3.6)

project(Battleship)
enable_language(ASM_NASM)
set_source_files_properties(BitArray2D.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)

add_subdirectory(src)

add_subdirectory(test)



