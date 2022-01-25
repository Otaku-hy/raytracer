aux_source_directory(. SourceList)

add_library(Integrator STATIC ${SourceList})

target_include_directories(Integrator PUBLIC .)