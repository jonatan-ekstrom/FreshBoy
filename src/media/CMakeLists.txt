# SDL2 C++ wrapper library (libmedia).

# List media header and source files.
set(mediaHeaders
    audio.h
    event_manager.h
    instance.h
    key.h
    renderer.h
    texture.h
    window.h
    wrapper.h)

set(mediaSources
    audio.cc
    event_manager.cc
    instance.cc
    key.cc
    renderer.cc
    texture.cc
    window.cc)

# Add the 'media' static library.
add_library(media STATIC ${mediaSources})

# Setup include directories.
target_include_directories(media INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Include the SDL headers.
target_include_directories(media SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})

# Reference the SDL libraries.
target_link_libraries(media PUBLIC ${SDL2_LIBRARIES})

# Tag library for installation.
install(TARGETS media DESTINATION lib)
install(FILES ${mediaHeaders} DESTINATION include/media)
