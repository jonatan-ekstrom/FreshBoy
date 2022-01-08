#include "mbc5.h"
#include <utility>
#include "bits.h"
#include "log.h"

namespace gb {

MBC5::MBC5(const Path& romPath, Header&& header)
    : MBC{romPath, std::move(header)},
      ramEnabled{false},
      romLow{0},
      romHigh{0},
      ramBank{0} {}

u8 MBC5::Read(const u16 address) const {
    if (address <= 0x3FFF) {
        return this->romBanks[0][address];
    }

    if (address >= 0x4000 && address <= 0x7FFF) {
        return this->romBanks[RomBank()][address - 0x4000];
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC5 - RAM read when disabled: " + log::Hex(address));
            return 0xFF;
        }
        return this->ramBanks[RamBank()][address - 0xA000];
    }

    log::Warning("MBC5 - Invalid read address: " + log::Hex(address));
    return 0xFF;
}

void MBC5::Write(const u16 address, const u8 byte) {
    if (address <= 0x1FFF) {
        this->ramEnabled = !this->ramBanks.empty() && ((byte & 0x0F) == 0x0A);
        return;
    }

    if (address >= 0x2000 && address <=0x2FFF) {
        this->romLow = byte;
        return;
    }

    if (address >= 0x3000 && address <= 0x3FFF) {
        this->romHigh = byte & 0x01;
        return;
    }

    if (address >= 0x4000 && address <= 0x5FFF) {
        this->ramBank = byte & 0x0F;
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC5 - RAM written when disabled: " + log::Hex(address));
            return;
        }
        this->ramBanks[RamBank()][address - 0xA000] = byte;
        return;
    }

    log::Warning("MBC5 - Invalid write address: " + log::Hex(address));
}

uint MBC5::RomBank() const {
    const auto merged{bit::Merge(this->romHigh, this->romLow)};
    const auto masked{merged & this->romBitMask};
    return static_cast<uint>(masked);
}

uint MBC5::RamBank() const {
    return static_cast<uint>(this->ramBank & this->ramBitMask);
}

}
