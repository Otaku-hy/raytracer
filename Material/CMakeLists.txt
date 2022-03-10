aux_source_directory(. SourceList)

add_library(Material STATIC ${SourceList})

target_link_libraries(Material PRIVATE BxDF)
target_include_directories(Material PUBLIC .)