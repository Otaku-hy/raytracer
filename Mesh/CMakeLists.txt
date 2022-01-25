aux_source_directory(. SourceList)

add_library(Mesh STATIC ${SourceList})

target_include_directories(Mesh PUBLIC .)