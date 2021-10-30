#include "rom.h"
#include <utility>
#include "file.h"
#include "log.h"

namespace gb {

RomOnly::RomOnly(const Path& romPath, Header&& header)
    : Cartridge_{std::move(header)} {
    // Open file and read the first 32 kB of data.
    InputFile file{romPath};
    this->rom = file.ReadBytes(0, 0x8000);
}

u8 RomOnly::Read(const u16 address) const {
    if (address > 0x7FFF) {
        log::Warning("RomOnly - Invalid address read: " + log::Hex(address));
        return 0xFF;
    }
    return rom[address];
}

void RomOnly::Write(const u16 address, u8) {
    log::Warning("RomOnly - Write to ROM area: " + log::Hex(address));
}

u16 RomOnly::Checksum() const {
    u16 sum{0};
    for (auto i{0u}; i < this->rom.size(); ++i) {
        if (i != 0x14E && i != 0x14F) {
            sum += this->rom[i];
        }
    }
    return sum;
}

}
