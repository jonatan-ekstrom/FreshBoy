#include "cartridge.h"
#include <stdexcept>
#include <utility>
#include "log.h"
#include "mbc1.h"
#include "mbc3.h"
#include "rom.h"

namespace fs = std::filesystem;

namespace gb {

Cartridge_::Cartridge_(Header&& header) : header{std::move(header)} {}

Cartridge Cartridge_::Create(const fs::path& romPath, const uint refreshRate) {
    Header header{romPath};
    const auto checksum{header.CartridgeChecksum()};

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

void Cartridge_::LoadRam(const fs::path&) {}

void Cartridge_::SaveRam(const fs::path&) {}

std::string Cartridge_::HeaderInfo() const { return this->header.PrettyPrint(); }

}
