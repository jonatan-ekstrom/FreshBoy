#pragma once
#include "mbc.h"
#include "types.h"
#include "path.h"

namespace gb {

class Header;

/* Handler class for MBC2 based cartridges. */
class MBC2 final : public MBC {
public:
    /* Creates a new MBC2 handler from the provided file. */
    MBC2(const Path& romPath, Header&& header);

    /* Read data from the provided address. */
    u8 Read(u16 address) const override;

    /* Write data to the provided address. */
    void Write(u16 address, u8 byte) override;
private:
    uint BankNumber() const;
    bool ramEnabled;
    u8 romBank;
};

}
