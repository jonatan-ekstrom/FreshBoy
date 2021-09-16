#pragma once
#include <string>
#include "mbc.h"
#include "types.h"

namespace gb {

class Header;

class MBC1 final : public MBC {
public:
    MBC1(const std::string& romPath, Header&& header);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
private:
    uint RomBankLow() const;
    uint RomBankHigh() const;
    uint RamBank() const;
    bool ramEnabled;
    bool advancedMode;
    u8 bankLow;
    u8 bankHigh;
};

}
