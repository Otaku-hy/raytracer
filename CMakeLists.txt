cmake_minimum_required(VERSION 2.8)

project(pbrt)

include_directories(Acceleration BxDF Camera Filter Integrator Light lib Material
Matrix4_4 Mesh Primitive Sample Scene Shape Interaction Utils Ray .)

add_compile_options(-std=c++11)

aux_source_directory(Acceleration SRC_LIST)
aux_source_directory(BxDF SRC_LIST)
aux_source_directory(Camera SRC_LIST)
aux_source_directory(Filter SRC_LIST)
aux_source_directory(Integrator SRC_LIST)
aux_source_directory(Light SRC_LIST)
aux_source_directory(lib SRC_LIST)
aux_source_directory(Material SRC_LIST)
aux_source_directory(Matrix4_4 SRC_LIST)
aux_source_directory(Ray SRC_LIST)
aux_source_directory(Primitive SRC_LIST)
aux_source_directory(Sample SRC_LIST)
aux_source_directory(Scene SRC_LIST)
aux_source_directory(Shape SRC_LIST)
aux_source_directory(Interaction SRC_LIST)
aux_source_directory(Mesh SRC_LIST)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(pbrt main.cpp ${SRC_LIST})
