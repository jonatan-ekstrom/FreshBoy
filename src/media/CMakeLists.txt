# Creates the 'media' static library.
set(mediaHeaders instance.h key.h window.h)
set(mediaSources instance.cc key.cc window.cc)
add_library(media STATIC ${mediaSources})
target_include_directories(media INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(media SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(media PUBLIC ${SDL2_LIBRARIES})
install(TARGETS media DESTINATION lib)
install(FILES ${mediaHeaders} DESTINATION include/media)
