aux_source_directory(. SourceList)

add_library(Matrix4_4 STATIC ${SourceList})

target_include_directories(Matrix4_4 PUBLIC .)