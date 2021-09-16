#include "mbc.h"
#include <utility>

namespace gb {

MBC::MBC(Header&& header) : Cartridge_{std::move(header)} {}

void MBC::LoadRam(const std::string& ramPath) {
    Cartridge_::LoadRam(ramPath);
}

void MBC::SaveRam(const std::string& ramPath) {
    Cartridge_::SaveRam(ramPath);
}

}
