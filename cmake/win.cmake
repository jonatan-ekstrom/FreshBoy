# This file contains CMake code specific for the MSVC compiler.

# List warning flags.
set(warningList
    /sdl
    /W3
    /WX)

set(instrumentationList
    /fsanitize=address)

set(debugList
    /EHsc
    /Od
    /RTC1
    /Z7)

set(releaseList
    /arch:AVX2
    /favor:INTEL64
    /EHsc
    /O2
    /Qpar)

# Add link-time optimization flag to release options if enabled.
if (USE_LTO)
    list(APPEND releaseList /GL)
endif ()

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
