#include "mbc2.h"
#include <utility>
#include "bits.h"
#include "log.h"

namespace gb {

MBC2::MBC2(const Path& romPath, Header&& header)
    : MBC{romPath, std::move(header)},
      ramEnabled{false},
      romBank{1} {}

u8 MBC2::Read(const u16 address) const {
    if (address <= 0x3FFF) {
        return this->romBanks[0][address];
    }

    if (address >= 0x4000 && address <= 0x7FFF) {
        return this->romBanks[BankNumber()][address - 0x4000];
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC2 - RAM read when disabled: " + log::Hex(address));
            return 0xFF;
        }
        const auto masked{static_cast<u16>(address & 0x1FF)};
        return this->ramBanks[0][masked];
    }

    log::Warning("MBC2 - Invalid read address: " + log::Hex(address));
    return 0xFF;
}

void MBC2::Write(const u16 address, const u8 byte) {
    if (address <= 0x3FFF) {
        const auto ram{bit::IsClear(address, 8)};
        if (ram) {
            this->ramEnabled = !this->ramBanks.empty() && ((byte & 0x0F) == 0x0A);
        } else {
            const auto number{static_cast<u8>(byte & 0x0F)};
            this->romBank = number != 0 ? number : 1;
        }
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if (!this->ramEnabled) {
            log::Warning("MBC2 - RAM written when disabled: " + log::Hex(address));
            return;
        }
        const auto masked{static_cast<u16>(address & 0x1FF)};
        const auto value{static_cast<u8>(byte & 0x0F)};
        this->ramBanks[0][masked] = value;
        return;
    }

    log::Warning("MBC2 - Invalid write address: " + log::Hex(address));
}

uint MBC2::BankNumber() const {
    return this->romBank & this->romBitMask;
}

}
