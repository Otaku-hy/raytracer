aux_source_directory(. SourceList)

add_library(Light STATIC ${SourceList})

target_include_directories(Light PUBLIC .)