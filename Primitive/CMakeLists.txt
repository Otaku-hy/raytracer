aux_source_directory(. SourceList)

add_library(Primitive STATIC ${SourceList})

target_include_directories(Primitive PUBLIC .)