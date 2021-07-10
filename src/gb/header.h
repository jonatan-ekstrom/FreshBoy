#pragma once

#include <cstdint>
#include <string>
#include <vector>

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
    explicit Header(const std::string& fileName);
    std::string Entry() const;
    std::string Logo() const;
    std::string Title() const;
    std::string ManufacturerCode() const;
    std::string CGBFlag() const;
    std::string NewLicenseeCode() const;
    std::string SGBFlag() const;
    CartridgeType Type() const;
    std::string TypeCode() const;
    std::string TypeStr() const;
    MemSize RomSize() const;
    std::string RomStr() const;
    MemSize RamSize() const;
    std::string RamStr() const;
    bool Japanese() const;
    std::string Licensee() const;
    std::uint8_t VersionNumber() const;
    std::uint8_t Checksum() const;
    std::uint8_t ComputedChecksum() const;
    std::uint16_t GlobalChecksum() const;
    std::string PrettyPrint() const;
private:
    std::string Stringify(std::uint16_t begin, std::uint16_t end) const;
    std::string Hexdump(std::uint16_t begin, std::uint16_t end) const;
    std::vector<std::uint8_t> bytes;
};

}
