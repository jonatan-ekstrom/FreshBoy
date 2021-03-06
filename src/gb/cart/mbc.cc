#include "mbc.h"
#include <utility>
#include "file.h"
#include "header.h"

namespace gb {

MBC::MBC(const Path& romPath, Header&& header)
    : Cartridge_{std::move(header)},
      romBitMask{0},
      ramBitMask{0} {
    constexpr auto romBankSize{0x4000};
    constexpr auto ramBankSize{0x2000};
    const auto numRomBanks{this->header.RomBanks()};
    const auto numRamBanks{this->header.RamBanks()};

    // Load all ROM banks from the file.
    InputFile file{romPath};
    for (auto i{0u}; i < numRomBanks; ++i) {
        const auto offset{i * romBankSize};
        this->romBanks.emplace_back(file.ReadBytes(offset, romBankSize));
    }

    // Allocate memory for all cartridge RAM banks.
    for (auto i{0u}; i < numRamBanks; ++i) {
        this->ramBanks.emplace_back(ramBankSize);
    }

    // Initialize bitmasks based on the number of banks available.
    this->romBitMask = static_cast<u8>(numRomBanks - 1);
    this->ramBitMask = numRamBanks != 0 ? static_cast<u8>(numRamBanks - 1) : 0;
}

void MBC::LoadRam(const Path& ramPath) {
    // Load cartridge RAM banks from previously saved data.
    InputFile file{ramPath};
    std::streampos offset{0};
    for (auto& bank : this->ramBanks) {
        const auto size{static_cast<std::streamsize>(bank.size())};
        bank = file.ReadBytes(offset, size);
        offset += size;
    }

    LoadHook(file, offset);
}

void MBC::SaveRam(const Path& ramPath) {
    // Save cartridge RAM banks to file.
    OutputFile file{ramPath};
    std::streampos offset{0};
    for (const auto& bank : this->ramBanks) {
        const auto size{static_cast<std::streamsize>(bank.size())};
        file.WriteBytes(offset, bank);
        offset += size;
    }

    SaveHook(file, offset);
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
        for (const auto byte : bank) {
            sum += byte;
        }
    }

    return sum;
}

void MBC::LoadHook(InputFile&, std::streampos) {}

void MBC::SaveHook(OutputFile&, std::streampos) {}

}
