#pragma once
#include <string>
#include <vector>
#include "path.h"
#include "types.h"

namespace gb {

enum class CartridgeType {
    Unknown,
    RomOnly,
    MBC1,
    MBC2,
    MBC3,
    MBC5,
    MBC6,
    MBC7
};

enum class MemSize {
    Unknown,
    Zero,
    KB8,
    KB32,
    KB64,
    KB128,
    KB256,
    KB512,
    MB1,
    MB2,
    MB4,
    MB8
};

class Header {
public:
    explicit Header(const Path& romPath);
    std::string Entry() const;
    std::string Logo() const;
    std::string Title() const;
    std::string NewLicenseeCode() const;
    std::string SgbFlag() const;
    CartridgeType Type() const;
    std::string TypeCode() const;
    std::string TypeStr() const;
    MemSize RomSize() const;
    std::string RomStr() const;
    uint RomBanks() const;
    MemSize RamSize() const;
    uint RamBanks() const;
    std::string RamStr() const;
    bool Japanese() const;
    std::string Licensee() const;
    u8 VersionNumber() const;
    u8 Checksum() const;
    u16 CartridgeChecksum() const;
    std::string PrettyPrint() const;
private:
    std::string Stringify(u16 begin, u16 end) const;
    std::string Hexdump(u16 begin, u16 end) const;
    u8 ComputedChecksum() const;
    std::vector<u8> bytes;
};

}
