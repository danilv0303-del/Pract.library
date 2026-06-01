cmake_minimum_required(VERSION 3.10)
project(LibraryApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

include_directories(src)
add_executable(LibraryApp
    src/main.cpp
    src/Book.cpp
    src/Library.cpp
    src/FileIO.cpp
    src/Menu.cpp
)

if(NOT MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(LibraryApp stdc++fs)
endif()