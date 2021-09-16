#pragma once
#include <string>
#include <vector>
#include "cartridge.h"

namespace gb {

class Header;

class MBC : public Cartridge_ {
public:
    void LoadRam(const std::string& ramPath) override final;
    void SaveRam(const std::string& ramPath) override final;
protected:
    MBC(const std::string& romPath, Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
    u8 romBitMask;
    u8 ramBitMask;
private:
    u16 Checksum() const override final;
};

}
