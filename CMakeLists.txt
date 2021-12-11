# We require at least version 3.18 of CMake.
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# Check status of build type and compiler flags.
if (DEFINED CMAKE_BUILD_TYPE)
    set(haveBuildType TRUE)
endif ()

if (DEFINED CMAKE_CXX_FLAGS)
    set(haveFlags TRUE)
endif ()

if (DEFINED CMAKE_CXX_FLAGS_DEBUG)
    set(haveDebugFlags TRUE)
endif ()

if (DEFINED CMAKE_CXX_FLAGS_RELEASE)
    set(haveReleaseFlags TRUE)
endif ()

# Create C++ project.
project(FreshBoy
        VERSION 1.0
        LANGUAGES CXX)

# Use C++20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add cmake directory to module search path.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Look for the SDL2 libraries, abort if not found.
find_package(SDL2 REQUIRED)

# Set build type to Release if not provided.
if (NOT haveBuildType)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif ()

# Make it possible to opt out from GNU specific flags (if unsupported by compiler).
option(USE_GNU_FLAGS "" ON)

if (USE_GNU_FLAGS AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Add GNU specific compiler flags
    include(gnu)
endif ()

# Parse the source directory
add_subdirectory(src)
