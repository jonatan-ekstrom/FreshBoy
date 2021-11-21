#include "types.h"

namespace {

/* Compile time test to verify that integers are at least 32-bits wide. */

using namespace gb;

constexpr uint BitCount() {
    auto i{static_cast<uint>(-1)};
    uint count{0};
    while (i != 0) {
        i >>= 1;
        ++count;
    }
    return count;
}

static_assert(BitCount() >= 32, "16-bit ints not supported.");

}
