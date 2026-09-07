cmake_minimum_required(VERSION 3.24)
project(puterforge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(puterforge WIN32
    main.cpp
)

target_compile_definitions(puterforge PRIVATE UNICODE _UNICODE)
target_link_libraries(puterforge PRIVATE user32)

if(MSVC)
    target_compile_options(puterforge PRIVATE /W4 /permissive-)
endif()
