aux_source_directory(. SourceList)

add_library(Camera STATIC ${SourceList})

target_include_directories(Camera PUBLIC .)