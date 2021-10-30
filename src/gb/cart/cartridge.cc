#include "cartridge.h"
#include <stdexcept>
#include <utility>
#include "log.h"
#include "mbc1.h"
#include "mbc3.h"
#include "rom.h"

namespace gb {

Cartridge_::Cartridge_(Header&& header) : header{std::move(header)} {}

Cartridge Cartridge_::Create(const Path& romPath, const uint refreshRate) {
    // Parse the header and compute the cartridge checksum.
    Header header{romPath};
    const auto checksum{header.CartridgeChecksum()};

    /* Check the cartridge type and create the proper derived class. */
    Cartridge res;
    switch (header.Type()) {
        case CartridgeType::RomOnly:
            res = std::make_shared<RomOnly>(romPath, std::move(header));
            break;
        case CartridgeType::MBC1:
            res = std::make_shared<MBC1>(romPath, std::move(header));
            break;
        case CartridgeType::MBC3:
            res = std::make_shared<MBC3>(romPath, std::move(header), refreshRate);
            break;
        case CartridgeType::MBC2:
        case CartridgeType::MBC5:
        case CartridgeType::MBC6:
        case CartridgeType::MBC7:
        case CartridgeType::Unknown:
        default:
            throw std::runtime_error{"Unsupported cartridge type."};
    }
    if (res->Checksum() != checksum) {
        log::Warning("Cartridge checksum mismatch.");
    }
    return res;
}

void Cartridge_::Tick(uint) {}

void Cartridge_::LoadRam(const Path&) {}

void Cartridge_::SaveRam(const Path&) {}

std::string Cartridge_::HeaderInfo() const { return this->header.PrettyPrint(); }

}
