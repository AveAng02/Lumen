
# TODO: Write a script that automates build

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Lumen VERSION 0.0.1)

include_directories(include)

add_executable(Lumen Main.cpp 
src/Vec3.h
src/Ray.h
src/MathUtils.h
src/Geometry.h
src/HitList.h
src/Sphere.h 
src/Pass.h
src/Camera.h
src/Integrator.h)

target_include_directories(Lumen PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
