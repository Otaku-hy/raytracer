aux_source_directory(. SourceList)

add_library(Scene STATIC ${SourceList})

# target_link_libraries(Scene PUBLIC Ray)
target_include_directories(Scene PUBLIC .)