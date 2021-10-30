#pragma once
#include "cartridge.h"
#include "path.h"
#include "types.h"

namespace gb {

class Header;

/* Handler class for ROM-only cartridges. */
class RomOnly final : public Cartridge_ {
public:
    /* Creates a new ROM-only handler from the provided file. */
    RomOnly(const Path& romPath, Header&& header);

    u8 Read(u16 address) const override;

    void Write(u16 address, u8 byte) override;
private:
    u16 Checksum() const override;
    MemBlock rom;
};

}
