#pragma once
#include <string>
#include "types.h"

namespace gb {

namespace log {

/* Enable logging. */
void Enable();

/* Convert a byte to a hexadecimal string representation. */
std::string Hex(u8 byte);

/* Convert a 16-bit address to a hexadecimal string representation. */
std::string Hex(u16 addr);

/* Log a warning. */
void Warning(const std::string& txt);

}

}
