# This file contains CMake code specific for the GNU compiler.

# List warning flags.
set(warningList
    -pedantic
    -Wall
    -Wextra
    -Werror)

set(instrumentationList
    -fsanitize=address
    -fsanitize=leak
    -fsanitize=undefined)

set(debugList
    -ggdb
    -O0)

set(releaseList
    -O3
    -flto
    -s
    -march=native
    -mtune=native)

# Setup build flags.
if (NOT haveFlags)
    list(JOIN warningList " " warningFlags)
    set(CMAKE_CXX_FLAGS "${warningFlags}" CACHE STRING "" FORCE)
endif ()

if (NOT haveDebugFlags)
    list(APPEND debugList ${instrumentationList})
    list(JOIN debugList " " debugFlags)
    set(CMAKE_CXX_FLAGS_DEBUG "${debugFlags}" CACHE STRING "" FORCE)
endif ()

if (NOT haveReleaseFlags)
    list(JOIN releaseList " " releaseFlags)
    set(CMAKE_CXX_FLAGS_RELEASE "${releaseFlags}" CACHE STRING "" FORCE)
endif ()
