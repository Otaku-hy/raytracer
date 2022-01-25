aux_source_directory(. SourceList)

add_library(Sample STATIC ${SourceList})

target_include_directories(Sample PUBLIC .)