# This file contains CMake code specific for the GNU compiler.

# List warning flags.
set(warningList
    -pedantic
    -pedantic-errors
    -Wall
    -Walloca
    -Walloc-zero
    -Warray-bounds=2
    -Wattribute-alias=2
    -Wcast-align=strict
    -Wcast-qual
    -Wcatch-value=3
    -Wclass-memaccess
    -Wconditionally-supported
    -Wconversion
    -Wctor-dtor-privacy
    -Wdate-time
    -Wdelete-non-virtual-dtor
    -Wdeprecated-copy
    -Wdeprecated-copy-dtor
    -Wdisabled-optimization
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Werror
    -Wextra
    -Wextra-semi
    -Wfloat-conversion
    -Wfloat-equal
    -Wformat=2
    -Wformat-nonliteral
    -Wformat-overflow=2
    -Wformat-security
    -Wformat-signedness
    -Wformat-truncation=2
    -Wformat-y2k
    -Wimplicit-fallthrough=5
    -Winit-self
    -Winvalid-pch
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-format-attribute
    -Wmissing-include-dirs
    -Wmultichar
    -Wmultiple-inheritance
    -Wnoexcept
    -Wnoexcept-type
    -Wnon-virtual-dtor
    -Wnormalized
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpacked
    -Wpessimizing-move
    -Wplacement-new=2
    -Wredundant-decls
    -Wredundant-move
    -Wregister
    -Wreorder
    -Wscalar-storage-order
    -Wshift-overflow=2
    -Wsign-conversion
    -Wsign-promo
    -Wstack-protector
    -Wstrict-aliasing=3
    -Wstrict-null-sentinel
    -Wstrict-overflow=5
    -Wstringop-overflow=4
    -Wsuggest-final-methods
    -Wsuggest-final-types
    -Wsuggest-override
    -Wswitch-default
    -Wswitch-enum
    -Wsynth
    -Wtrampolines
    -Wundef
    -Wunreachable-code
    -Wunsafe-loop-optimizations
    -Wunused-const-variable=2
    -Wunused-macros
    -Wuseless-cast
    -Wvector-operation-performance
    -Wvirtual-inheritance
    -Wwrite-strings
    -Wzero-as-null-pointer-constant)

set(instrumentationList
    -fsanitize-address-use-after-scope
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

# Setup build type and debug/release flags.
if (NOT haveBuildType)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif ()

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

