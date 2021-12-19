#pragma once
#include <string>
#include <vector>
#include "path.h"
#include "types.h"

namespace gb {

/* Enumeration of known Game Boy cartridge types. */
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

/* Enumeration of known memory sizes. */
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

/* Represents the Game Boy ROM header. */
class Header {
public:
    /* Creates a new header by parsing the provided ROM file. */
    explicit Header(const Path& romPath);

    /* Entry point */
    std::string Entry() const;

    /* Logo data */
    std::string Logo() const;

    /* ROM title */
    std::string Title() const;

    /* Licensee code (new) */
    std::string NewLicenseeCode() const;

    /* Super GameBoy flag */
    std::string SgbFlag() const;

    /* Cartridge type */
    CartridgeType Type() const;

    /* Cartridge type code */
    std::string TypeCode() const;

    /* Cartridge type string */
    std::string TypeStr() const;

    /* Size of the ROM banks. */
    MemSize RomSize() const;

    /* ROM size as a string */
    std::string RomStr() const;

    /* Number of ROM banks */
    uint RomBanks() const;

    /* Size of the RAM banks */
    MemSize RamSize() const;

    /* Number of RAM banks */
    uint RamBanks() const;

    /* RAM size as a string */
    std::string RamStr() const;

    /* True if a Japanese game */
    bool Japanese() const;

    /* Licensee */
    std::string Licensee() const;

    /* ROM version number */
    u8 VersionNumber() const;

    /* Header checksum */
    u8 Checksum() const;

    /* Cartridge checksum */
    u16 CartridgeChecksum() const;

    /* All header data pretty printed */
    std::string PrettyPrint() const;
private:
    std::string Stringify(u16 begin, u16 end) const;
    std::string Hexdump(u16 begin, u16 end) const;
    u8 ComputedChecksum() const;
    std::vector<u8> bytes;
};

}
