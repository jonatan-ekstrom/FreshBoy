#include "mbc.h"
#include <utility>

namespace gb {

MBC::MBC(Header&& header) : Cartridge_{std::move(header)} {}

}
