# Creates the 'gb' static library.
set(gbHeaders cartridge.h demo.h file.h header.h tile_bank.h)
set(gbSources cartridge.cc demo.cc file.cc header.cc tile_bank.cc)
add_library(gb STATIC ${gbSources})
target_include_directories(gb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gb PUBLIC media)
install(TARGETS gb DESTINATION lib)
install(FILES ${gbHeaders} DESTINATION include/gb)
