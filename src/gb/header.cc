#include "header.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

constexpr std::size_t HeaderOffset{0x100};
constexpr std::size_t HeaderSize{80};

std::string MemSizeToStr(const gb::MemSize sz) {
    using gb::MemSize;
    switch (sz) {
        case MemSize::Zero:
            return "None";
        case MemSize::KB8:
            return "8 KB";
        case MemSize::KB32:
            return "32 KB";
        case MemSize::KB64:
            return "64 KB";
        case MemSize::KB128:
            return "128 KB";
        case MemSize::KB256:
            return "256 KB";
        case MemSize::KB512:
            return "512 KB";
        case MemSize::MB1:
            return "1 MB";
        case MemSize::MB2:
            return "2 MB";
        case MemSize::MB4:
            return "4 MB";
        case MemSize::MB8:
            return "8 MB";
        case MemSize::Unknown:
        default:
            return "Unknown";
    }
}

}

namespace gb {

Header::Header(const std::string& fileName) {
    using Byte = std::fstream::char_type;
    constexpr auto flags{std::ios::in | std::ios::binary};

    std::fstream file{fileName, flags};
    if (!file) {
        throw std::runtime_error{"Failed to open file: " + fileName};
    }
    file.seekg(HeaderOffset);
    if (!file) {
        throw std::runtime_error{"Failed to seek to header offset."};
    }
    this->data.reset(new std::uint8_t[HeaderSize]);
    file.read(reinterpret_cast<Byte*>(this->data.get()), HeaderSize);
    if (file.gcount() != HeaderSize) {
        throw std::runtime_error{"Failed to read entire header."};
    }
}

std::string Header::Entry() const {
    return Hexdump(0x100, 0x103);
}

std::string Header::Logo() const {
    return Hexdump(0x104, 0x133);
}

std::string Header::Title() const {
    return Stringify(0x134, 0x143);
}

std::string Header::ManufacturerCode() const {
    return Stringify(0x13F, 0x142);
}

std::string Header::CGBFlag() const {
    return Hexdump(0x143, 0x143);
}

std::string Header::NewLicenseeCode() const {
    return Stringify(0x144, 0x145);
}

std::string Header::SGBFlag() const {
    return Hexdump(0x146, 0x146);
}

CartridgeType Header::Type() const {
    const auto byte{this->data[0x147 - HeaderOffset]};
    switch (byte) {
        case 0x00:
        case 0x08:
        case 0x09:
            return CartridgeType::RomOnly;

        case 0x01:
        case 0x02:
        case 0x03:
            return CartridgeType::MBC1;

        case 0x05:
        case 0x06:
            return CartridgeType::MBC2;

        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            return CartridgeType::MBC3;

        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return CartridgeType::MBC5;

        case 0x20:
            return CartridgeType::MBC6;

        case 0x22:
            return CartridgeType::MBC7;

        default:
            return CartridgeType::Unknown;
    }
}

std::string Header::TypeCode() const {
    return Hexdump(0x147, 0x147);
}

std::string Header::TypeStr() const {
    switch (Type()) {
        case CartridgeType::RomOnly:
            return "ROM only";
        case CartridgeType::MBC1:
            return "MBC1";
        case CartridgeType::MBC2:
            return "MBC2";
        case CartridgeType::MBC3:
            return "MBC3";
        case CartridgeType::MBC5:
            return "MBC5";
        case CartridgeType::MBC6:
            return "MBC6";
        case CartridgeType::MBC7:
            return "MBC7";
        case CartridgeType::Unknown:
        default:
            return "Unknown";
    }
}

MemSize Header::RomSize() const {
    const auto byte{this->data[0x148 - HeaderOffset]};
    switch (byte) {
        case 0x00:
            return MemSize::KB32;
        case 0x01:
            return MemSize::KB64;
        case 0x02:
            return MemSize::KB128;
        case 0x03:
            return MemSize::KB256;
        case 0x04:
            return MemSize::KB512;
        case 0x05:
            return MemSize::MB1;
        case 0x06:
            return MemSize::MB2;
        case 0x07:
            return MemSize::MB4;
        case 0x08:
            return MemSize::MB8;
        default:
            return MemSize::Unknown;
    }
}

std::string Header::RomStr() const {
    return MemSizeToStr(RomSize());
}

MemSize Header::RamSize() const {
    const auto byte{this->data[0x149 - HeaderOffset]};
    switch (byte) {
        case 0x00:
            return MemSize::Zero;
        case 0x02:
            return MemSize::KB8;
        case 0x03:
            return MemSize::KB32;
        case 0x04:
            return MemSize::KB128;
        case 0x05:
            return MemSize::KB64;
        default:
            return MemSize::Unknown;
    }
}

std::string Header::RamStr() const {
    return MemSizeToStr(RamSize());
}

bool Header::Japanese() const {
    return this->data[0x14A - HeaderOffset] == 0;
}

std::string Header::Licensee() const {
    return Hexdump(0x14B, 0x14B);
}

std::uint8_t Header::VersionNumber() const {
    return this->data[0x14C - HeaderOffset];
}

std::uint8_t Header::Checksum() const {
    return this->data[0x14D - HeaderOffset];
}

std::uint8_t Header::ComputedChecksum() const {
    std::uint8_t checksum{0};
    const auto begin{this->data.get() + 0x134 - HeaderOffset};
    const auto end{this->data.get() + 0x14D - HeaderOffset};
    for (auto p{begin}; p != end; ++p) {
        checksum = static_cast<std::uint8_t>(checksum - *p - 1);
    }
    return checksum;
}

std::uint16_t Header::GlobalChecksum() const {
    const auto upper{this->data[0x14E - HeaderOffset]};
    const auto lower{this->data[0x14F - HeaderOffset]};
    return static_cast<uint16_t>(upper << 8 | lower);
}

std::string Header::Stringify(const std::size_t begin, const std::size_t end) const {
    const auto start{this->data.get() + begin - HeaderOffset};
    const auto stop{this->data.get() + end - HeaderOffset + 1};
    std::unique_ptr<char[]> characters{new char[end - begin + 2]};
    characters[end - begin + 1] = '\0';
    std::copy(start, stop, characters.get());
    return std::string(characters.get());
}

std::string Header::Hexdump(const std::size_t begin, const std::size_t end) const {
    const char characters[]{"0123456789ABCDEF"};
    const auto start{this->data.get() + begin - HeaderOffset};
    const auto stop{this->data.get() + end - HeaderOffset + 1};
    std::string result;
    int count{};
    for (auto p{start}; p != stop; ++p) {
        const auto byte{*p};
        const auto upper{(byte & 0xF0) >> 4};
        const auto lower{byte & 0x0F};
        result.push_back(characters[upper]);
        result.push_back(characters[lower]);
        if (++count == 16) {
            result.push_back('\n');
            count = 0;
        } else if (p != stop - 1) {
            result.push_back(' ');
        }
    }
    return result;
}

std::string Header::PrettyPrint() const {
    std::ostringstream ss;
    ss << "------------ Contents of ROM header ------------\n"
       << "Title: " << Title() << '\n'
       << "Type: " << TypeCode() << " - " << TypeStr() << '\n'
       << "Version: " << static_cast<int>(VersionNumber()) << '\n'
       << "ROM Size: " << RomStr() << '\n'
       << "RAM Size: " << RamStr() << '\n'
       << "Japanese: " << (Japanese() ? "Yes" : "No") << '\n'
       << "Licensee: " << Licensee() << '\n'
       << "New Licensee: " << NewLicenseeCode() << '\n'
       << "Manufacturer: " << ManufacturerCode() << '\n'
       << "CGB Flag: " << CGBFlag() << '\n'
       << "SGB Flag: " << SGBFlag() << '\n'
       << "Entry: " << Entry() << '\n'
       << "--------------------- Logo ---------------------\n"
       << Logo()
       << "------------------------------------------------\n"
       << "Checksum: " << static_cast<int>(Checksum()) << '\n'
       << "Computed checksum: " << static_cast<int>(ComputedChecksum()) << '\n'
       << "Global checksum: " << GlobalChecksum() << std::endl;
    return ss.str();
}

}
