aux_source_directory(. SourceList)
add_library(Shape STATIC ${SourceList})

# target_link_libraries(Shape PUBLIC Material BxDF)
target_include_directories(Shape PUBLIC .)
