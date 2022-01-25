aux_source_directory(. SourceList)

add_library(BxDF STATIC ${SourceList})

target_include_directories(BxDF PUBLIC .)