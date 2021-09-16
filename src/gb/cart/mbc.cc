#include "mbc.h"
#include <utility>

namespace gb {

MBC::MBC(Header&& header)
    : Cartridge_{std::move(header)} {}

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
