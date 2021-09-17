#pragma once
#include <filesystem>
#include <vector>
#include "cartridge.h"

namespace gb {

class Header;

class MBC : public Cartridge_ {
public:
    void LoadRam(const std::filesystem::path& ramPath) override final;
    void SaveRam(const std::filesystem::path& ramPath) override final;
protected:
    MBC(const std::filesystem::path& romPath, Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
    u8 romBitMask;
    u8 ramBitMask;
private:
    u16 Checksum() const override final;
};

}
