aux_source_directory(. SourceList)

add_library(Acceleration STATIC ${SourceList})

target_include_directories(Acceleration PUBLIC .)