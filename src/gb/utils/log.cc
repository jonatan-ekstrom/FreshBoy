#include "log.h"
#include <iostream>

namespace {
    constexpr char Chars[]{"0123456789ABCDEF"};
    bool Enabled{false};
}

namespace gb::log {

void Enable() { Enabled = true; }

std::string Hex(const u8 byte) {
    std::string res{"0x"};
    res.push_back(Chars[(byte >> 4) & 0x0F]);
    res.push_back(Chars[byte & 0x0F]);
    return res;
}

std::string Hex(const u16 address) {
    std::string res{"0x"};
    res.push_back(Chars[(address >> 12) & 0x0F]);
    res.push_back(Chars[(address >> 8) & 0x0F]);
    res.push_back(Chars[(address >> 4) & 0x0F]);
    res.push_back(Chars[address & 0x0F]);
    return res;
}

void Warning(const std::string& txt) {
    if (!Enabled) return;
    std::cout << "WARN: " + txt << std::endl;
}

}
