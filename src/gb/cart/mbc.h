#pragma once
#include <vector>
#include "cartridge.h"

namespace gb {

class Header;

class MBC : public Cartridge_ {
protected:
    explicit MBC(Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
};

}
