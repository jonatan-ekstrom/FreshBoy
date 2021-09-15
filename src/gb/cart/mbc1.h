#pragma once
#include <string>
#include "mbc.h"
#include "types.h"

namespace gb {

class Header;

class MBC1 final : public MBC {
public:
    MBC1(const std::string& filePath, Header&& header);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
private:
    uint RomBankLow() const;
    uint RomBankHigh() const;
    uint RamBank() const;
    u16 Checksum() const override;
    bool ramEnabled;
    bool advancedMode;
    u8 bankLow;
    u8 bankHigh;
    u8 romBitMask;
    u8 ramBitMask;
};

}
