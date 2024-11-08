cmake_minimum_required(VERSION 3.10)

project(raytracing_one_weekend)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
set(SOURCE src/main.cc src/vec3.h src/color.h)

add_executable(main ${SOURCE})
