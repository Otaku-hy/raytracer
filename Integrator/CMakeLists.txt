aux_source_directory(. SourceList)

add_library(Integrator STATIC ${SourceList})

target_link_libraries(Integrator PUBLIC OpenMP::OpenMP_CXX)
target_include_directories(Integrator PUBLIC .)