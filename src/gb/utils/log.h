#pragma once
#include <string>
#include "types.h"

namespace gb {

namespace log {

void Enable();

std::string Hex(u16 addr);

void Warning(const std::string& txt);

}

}
