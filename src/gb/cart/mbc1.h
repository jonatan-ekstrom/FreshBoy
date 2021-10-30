#pragma once
#include "mbc.h"
#include "types.h"
#include "path.h"

namespace gb {

class Header;

/* Handler class for MBC1 based cartridges. */
class MBC1 final : public MBC {
public:
    /* Creates a new MBC1 handler from the provided file. */
    MBC1(const Path& romPath, Header&& header);

    u8 Read(u16 address) const override;

    void Write(u16 address, u8 byte) override;
private:
    uint RomBankLow() const;
    uint RomBankHigh() const;
    uint RamBank() const;
    bool ramEnabled;
    bool advancedMode;
    u8 bankLow;
    u8 bankHigh;
};

}
