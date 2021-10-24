#include "mbc1.h"
#include <utility>
#include "log.h"

namespace gb {

MBC1::MBC1(const Path& romPath, Header&& header)
    : MBC{romPath, std::move(header)},
      ramEnabled{false},
      advancedMode{false},
      bankLow{1},
      bankHigh{0} {}

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

}
