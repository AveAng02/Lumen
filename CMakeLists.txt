
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Lumen VERSION 0.0.1)

include_directories(include)

add_executable(Lumen Main.cpp 
include/Vec3.h
include/Ray.h
include/Sphere.h 
include/Pass.h)

target_include_directories(Lumen PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
