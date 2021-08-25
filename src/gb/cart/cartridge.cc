#include "cartridge.h"
#include <stdexcept>
#include <utility>
#include "file.h"
#include "header.h"
#include "log.h"

namespace {

constexpr gb::u8 GetRomBitMask(const gb::uint romBanks) {
    using namespace gb;
    auto tmp{romBanks};
    auto shift{0};
    u8 mask{0};
    while (tmp != 0) {
        mask = mask | static_cast<u8>(1 << shift);
        tmp = tmp >> 1;
        ++shift;
    }
    return mask;
}

}

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
      ramEnable{0},
      bankLow{1},
      bankHigh{0},
      modeSelect{0},
      romBitMask{0} {
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
        const auto offset{i * ramBankSize};
        this->ramBanks.push_back(file.ReadBytes(offset, ramBankSize));
    }

    this->romBitMask = GetRomBitMask(numRomBanks);
}

u8 MBC1::Read(const u16 address) const {
    if (address <= 0x3FFF) {
        return this->romBanks[RomBankLow()][address];
    }

    if (address >= 0x4000 && address <= 0x7FFF) {
        return this->romBanks[RomBankHigh()][address - 0x4000];
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!RamEnabled()) {
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
        this->ramEnable = byte;
        return;
    }

    if (address >= 0x2000 && address <=0x3FFF) {
        this->bankLow = byte;
        return;
    }

    if (address >= 0x4000 && address <= 0x5FFF) {
        this->bankHigh = byte;
        return;
    }

    if (address >= 0x6000 && address <= 0x7FFF) {
        this->modeSelect = byte;
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!RamEnabled()) {
            log::Warning("MBC1 - RAM written when disabled: " + log::Hex(address));
            return;
        }
        this->ramBanks[RamBank()][address - 0xA000] = byte;
        return;
    }

    log::Warning("MBC1 - Invalid write address: " + log::Hex(address));
}


bool MBC1::RamEnabled() const {
    return (this->ramEnable & 0x0F) == 0x0A;
}

uint MBC1::RomBankLow() const {
    if (!AdvancedMode()) {
        return 0;
    }
    return (this->bankHigh & 0x03u) << 5;
}

uint MBC1::RomBankHigh() const {
    auto lowFive{(this->bankLow & this->romBitMask) & 0x1Fu};
    if (lowFive == 0) {
        lowFive = 1;
    }
    const auto upperTwo{this->bankHigh & 0x03u};
    return (upperTwo << 5) | lowFive;
}

uint MBC1::RamBank() const {
    if (!AdvancedMode()) {
        return 0;
    }
    return this->bankHigh & 0x03;
}

bool MBC1::AdvancedMode() const {
    return (this->modeSelect & 0x01) != 0;
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
