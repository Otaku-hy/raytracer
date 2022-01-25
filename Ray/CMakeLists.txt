aux_source_directory(. SourceList)

add_library(Ray STATIC ${SourceList})

target_include_directories(Ray PUBLIC .)