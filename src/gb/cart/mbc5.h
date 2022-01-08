#pragma once
#include "mbc.h"
#include "types.h"
#include "path.h"

namespace gb {

class Header;

/* Handler class for MBC5 based cartridges. */
class MBC5 final : public MBC {
public:
    /* Creates a new MBC5 handler from the provided file. */
    MBC5(const Path& romPath, Header&& header);

    u8 Read(u16 address) const override;

    void Write(u16 address, u8 byte) override;
private:
    uint RomBank() const;
    uint RamBank() const;
    bool ramEnabled;
    u8 romLow;
    u8 romHigh;
    u8 ramBank;
};

}
