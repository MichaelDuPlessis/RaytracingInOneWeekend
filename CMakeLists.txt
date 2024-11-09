cmake_minimum_required(VERSION 3.10)

project(raytracing_one_weekend)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cc ${SOURCE_DIR}/vec3.h ${SOURCE_DIR}/color.h ${SOURCE_DIR}/ray.h)

add_executable(main ${SOURCE})
