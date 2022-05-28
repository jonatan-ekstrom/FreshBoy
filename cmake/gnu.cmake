# This file contains CMake code specific for the GNU compiler.

# List warning flags.
set(warningList
    -pedantic
    -Wall
    -Wextra
    -Werror
    -Waligned-new=all
    -Walloc-zero
    -Walloca
    -Wanalyzer-too-complex
    -Warray-bounds=2
    -Wattribute-alias=2
    -Wcast-align=strict
    -Wcast-qual
    -Wcatch-value=3
    -Wclass-conversion
    -Wclass-memaccess
    -Wcomma-subscript
    -Wcomments
    -Wconditionally-supported
    -Wconversion
    -Wconversion-null
    -Wctor-dtor-privacy
    -Wdate-time
    -Wdelete-incomplete
    -Wdelete-non-virtual-dtor
    -Wdeprecated-copy
    -Wdeprecated-copy-dtor
    -Wduplicated-branches
    -Wduplicated-cond
    -Wextra-semi
    -Wfloat-conversion
    -Wfloat-equal
    -Wformat-nonliteral
    -Wformat-overflow=2
    -Wformat-signedness
    -Wformat-truncation=2
    -Wformat-y2k
    -Wformat=2
    -Wimplicit-fallthrough=5
    -Winaccessible-base
    -Winherited-variadic-ctor
    -Winit-list-lifetime
    -Winvalid-offsetof
    -Winvalid-pch
    -Wliteral-suffix
    -Wlogical-op
    -Wmismatched-tags
    -Wmissing-format-attribute
    -Wmissing-include-dirs
    -Wmultichar
    -Wmultiple-inheritance
    -Wnon-template-friend
    -Wnon-virtual-dtor
    -Wnormalized=nfkc
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpacked
    -Wplacement-new=2
    -Wpmf-conversions
    -Wredundant-decls
    -Wredundant-move
    -Wredundant-tags
    -Wregister
    -Wscalar-storage-order
    -Wshift-overflow=2
    -Wsign-conversion
    -Wsign-promo
    -Wsized-deallocation
    -Wstack-protector
    -Wstrict-aliasing=3
    -Wstrict-null-sentinel
    -Wstrict-overflow=2
    -Wstringop-overflow=4
    -Wsubobject-linkage
    -Wsuggest-final-methods
    -Wsuggest-final-types
    -Wsuggest-override
    -Wswitch-default
    -Wswitch-enum
    -Wsynth
    -Wterminate
    -Wtrampolines
    -Wundef
    -Wunreachable-code
    -Wunsafe-loop-optimizations
    -Wunused-const-variable=2
    -Wunused-macros
    -Wuseless-cast
    -Wvirtual-inheritance
    -Wvirtual-move-assign
    -Wvolatile
    -Wwrite-strings
    -Wzero-as-null-pointer-constant)

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
