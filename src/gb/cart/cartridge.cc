#include "cartridge.h"
#include <stdexcept>
#include <utility>
#include "file.h"
#include "header.h"
#include "log.h"

namespace gb {

Cartridge_::Cartridge_(Header&& header) : header{std::move(header)} {}

Cartridge Cartridge_::Create(const std::string& filePath) {
    Header header{filePath};
    const auto checksum{header.CartridgeChecksum()};

    Cartridge res;
    switch (header.Type()) {
        case CartridgeType::RomOnly:
            res = std::make_shared<RomOnly>(filePath, std::move(header));
            break;
        case CartridgeType::MBC1:
            res = std::make_shared<MBC1>(filePath, std::move(header));
            break;
        case CartridgeType::MBC2:
        case CartridgeType::MBC3:
        case CartridgeType::MBC5:
        case CartridgeType::MBC6:
        case CartridgeType::MBC7:
        case CartridgeType::Unknown:
        default:
            throw std::runtime_error{"Unsupported cartridge type."};
    }
    if (res->Checksum() != checksum) {
        log::Warning("Cartridge checksum mismatch.");
    }
    return res;
}

std::string Cartridge_::HeaderInfo() const { return this->header.PrettyPrint(); }

RomOnly::RomOnly(const std::string& filePath, Header&& header)
    : Cartridge_{std::move(header)} {
    File file{filePath};
    this->rom = file.ReadBytes(0, 0x7FFF);
}

u8 RomOnly::Read(const u16 address) const {
    if (address > 0x7FFF) {
        log::Warning("RomOnly - Invalid address read: " + log::Hex(address));
        return 0xFF;
    }
    return rom[address];
}

void RomOnly::Write(const u16 address, u8) {
    log::Warning("RomOnly - Write to ROM area: " + log::Hex(address));
}

u16 RomOnly::Checksum() const {
    u16 sum{0};
    for (auto i{0u}; i < this->rom.size(); ++i) {
        if (i != 0x14E && i != 0x14F) {
            sum += this->rom[i];
        }
    }
    return sum;
}

MBC::MBC(Header&& header) : Cartridge_{std::move(header)} {}

MBC1::MBC1(const std::string& filePath, Header&& header)
    : MBC{std::move(header)},
      ramEnabled{false},
      advancedMode{false},
      bankLow{1},
      bankHigh{0},
      romBitMask{0},
      ramBitMask{0} {
    constexpr auto romBankSize{0x4000};
    constexpr auto ramBankSize{0x2000};
    const auto numRomBanks{this->header.RomBanks()};
    const auto numRamBanks{this->header.RamBanks()};

    File file{filePath};
    for (auto i{0u}; i < numRomBanks; ++i) {
        const auto offset{i * romBankSize};
        this->romBanks.push_back(file.ReadBytes(offset, romBankSize));
    }

    for (auto i{0u}; i < numRamBanks; ++i) {
        this->ramBanks.push_back(MemBlock(ramBankSize));
    }

    this->romBitMask = static_cast<u8>(numRomBanks - 1);
    this->ramBitMask = numRamBanks != 0 ? static_cast<u8>(numRamBanks - 1) : 0;
}

u8 MBC1::Read(const u16 address) const {
    if (address <= 0x3FFF) {
        return this->romBanks[RomBankLow()][address];
    }

    if (address >= 0x4000 && address <= 0x7FFF) {
        return this->romBanks[RomBankHigh()][address - 0x4000];
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC1 - RAM read when disabled: " + log::Hex(address));
            return 0xFF;
        }
        return this->ramBanks[RamBank()][address - 0xA000];
    }

    log::Warning("MBC1 - Invalid read address: " + log::Hex(address));
    return 0xFF;
}

void MBC1::Write(const u16 address, const u8 byte) {
    if (address <= 0x1FFF) {
        this->ramEnabled = !this->ramBanks.empty() && ((byte & 0x0F) == 0x0A);
        return;
    }

    if (address >= 0x2000 && address <=0x3FFF) {
        this->bankLow = byte & 0x1F;
        if (this->bankLow == 0) this->bankLow = 1;
        return;
    }

    if (address >= 0x4000 && address <= 0x5FFF) {
        this->bankHigh = byte & 0x03;
        return;
    }

    if (address >= 0x6000 && address <= 0x7FFF) {
        this->advancedMode = (byte & 0x01) != 0;
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC1 - RAM written when disabled: " + log::Hex(address));
            return;
        }
        this->ramBanks[RamBank()][address - 0xA000] = byte;
        return;
    }

    log::Warning("MBC1 - Invalid write address: " + log::Hex(address));
}

uint MBC1::RomBankLow() const {
    if (!this->advancedMode) {
        return 0;
    }
    return static_cast<uint>((this->bankHigh << 5) & this->romBitMask);
}

uint MBC1::RomBankHigh() const {
    return static_cast<uint>(((this->bankHigh << 5) | this->bankLow) & this->romBitMask);
}

uint MBC1::RamBank() const {
    if (!this->advancedMode) {
        return 0;
    }
    return static_cast<uint>(this->bankHigh & this->ramBitMask);
}

u16 MBC1::Checksum() const {
    u16 sum{0};
    const auto& bank0{this->romBanks[0]};
    for (auto i{0u}; i < bank0.size(); ++i) {
        if (i != 0x14E && i != 0x14F) {
            sum += bank0[i];
        }
    }

    for (auto b{1u}; b < this->romBanks.size(); ++b) {
        const auto& bank{this->romBanks[b]};
        for (const auto byte : bank) {
            sum += byte;
        }
    }

    return sum;
}

}
