#pragma once
#include <filesystem>
#include "cartridge.h"
#include "types.h"

namespace gb {

class Header;

class RomOnly final : public Cartridge_ {
public:
    RomOnly(const std::filesystem::path& romPath, Header&& header);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
private:
    u16 Checksum() const override;
    MemBlock rom;
};

}
