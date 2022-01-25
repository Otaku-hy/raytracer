aux_source_directory(. SourceList)

add_library(Filter STATIC ${SourceList})

target_include_directories(Filter PUBLIC .)