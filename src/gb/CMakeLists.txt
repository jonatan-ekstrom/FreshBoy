# Creates the 'gb' static library.
set(gbHeaders demo.h file.h header.h memblock.h)
set(gbSources demo.cc file.cc header.cc memblock.cc)
add_library(gb STATIC ${gbSources})
target_include_directories(gb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gb PUBLIC media)
install(TARGETS gb DESTINATION lib)
install(FILES ${gbHeaders} DESTINATION include/gb)
