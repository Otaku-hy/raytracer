aux_source_directory(. SourceList)

add_library(Material STATIC ${SourceList})

# target_link_libraries(Material PUBLIC BxDF Ray)
target_include_directories(Material PUBLIC .)