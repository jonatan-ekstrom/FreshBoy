# Add util sources
target_sources(gb PRIVATE log.cc test.cc)

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
