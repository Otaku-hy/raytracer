aux_source_directory(. SourceList)

add_library(Interaction STATIC ${SourceList})

target_include_directories(Interaction PUBLIC .)