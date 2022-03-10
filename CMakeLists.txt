cmake_minimum_required(VERSION 3.12)

project(pbrt LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Release")

add_compile_definitions(FLT_MAX=3.40282346638528859812e+38F)

find_package(OpenMP REQUIRED)
# add_compile_options(-fopenmp)

include_directories(lib Utils .)
include_directories(Acceleration BxDF Camera Filter Integrator Interaction Light Material Matrix4_4 Mesh Primitive Ray Shape Sample Scene)

add_subdirectory(Shape)
add_subdirectory(Acceleration)
add_subdirectory(BxDF)
add_subdirectory(Camera)
add_subdirectory(Filter)
add_subdirectory(Integrator)
add_subdirectory(Interaction)
add_subdirectory(Light)
add_subdirectory(Material)
add_subdirectory(Matrix4_4)
add_subdirectory(Mesh)
add_subdirectory(Primitive)
add_subdirectory(Ray)
add_subdirectory(Sample)
add_subdirectory(Scene)

add_executable(pbrt main.cpp)

set_target_properties(pbrt PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_link_libraries(pbrt PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(pbrt PUBLIC Shape Acceleration BxDF Camera Filter Integrator Interaction Light Material Matrix4_4 Mesh Primitive Ray Sample Scene)
