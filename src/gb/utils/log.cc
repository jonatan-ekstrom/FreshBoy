#include "log.h"
#include <iostream>

namespace gb::log {

std::string Hex(const u16 address) {
    constexpr char c[]{"0123456789ABCDEF"};
    std::string res{"0x"};
    res.push_back(c[(address >> 12) & 0x0F]);
    res.push_back(c[(address >> 8) & 0x0F]);
    res.push_back(c[(address >> 4) & 0x0F]);
    res.push_back(c[address & 0x0F]);
    return res;
}

void Warning(const std::string& txt) {
    std::cout << "WARN: " + txt << std::endl;
}

}
