#include "mbc.h"
#include <utility>
#include "file.h"
#include "header.h"

namespace gb {

MBC::MBC(const std::string& romPath, Header&& header)
    : Cartridge_{std::move(header)},
      romBitMask{0},
      ramBitMask{0} {
    constexpr auto romBankSize{0x4000};
    constexpr auto ramBankSize{0x2000};
    const auto numRomBanks{this->header.RomBanks()};
    const auto numRamBanks{this->header.RamBanks()};

    InputFile file{romPath};
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

void MBC::LoadRam(const std::string& ramPath) {
    Cartridge_::LoadRam(ramPath);
}

void MBC::SaveRam(const std::string& ramPath) {
    Cartridge_::SaveRam(ramPath);
}

u16 MBC::Checksum() const {
    u16 sum{0};
    const auto& bank0{this->romBanks[0]};
    for (auto i{0u}; i < bank0.size(); ++i) {
        if (i != 0x14E && i != 0x14F) {
            sum += bank0[i];
        }
    }

    for (auto b{1u}; b < this->romBanks.size(); ++b) {
        const auto& bank{this->romBanks[b]};
        for (const auto byte: bank) {
            sum += byte;
        }
    }

    return sum;
}

}
