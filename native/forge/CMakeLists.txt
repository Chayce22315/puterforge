cmake_minimum_required(VERSION 3.24)
project(puterforge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(puterforge WIN32
    main.cpp
    AppState.cpp
    AppState.h
    NativeWindow.cpp
    NativeWindow.h
)

target_compile_definitions(puterforge PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(puterforge PRIVATE user32 gdi32 shell32)
