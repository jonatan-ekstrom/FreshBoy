#pragma once
#include <vector>
#include "cartridge.h"

namespace gb {

class Header;

class MBC : public Cartridge_ {
public:
    void LoadRam(const std::string& ramPath) override final;
    void SaveRam(const std::string& ramPath) override final;
protected:
    explicit MBC(Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
private:
    u16 Checksum() const override final;
};

}
