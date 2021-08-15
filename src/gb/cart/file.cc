#include "file.h"
#include <cstddef>

namespace gb {

File::File(const std::string& filePath) : stream{filePath, std::ios::binary} {
    if (!this->stream) {
        throw std::runtime_error{"Failed to open file: " + filePath};
    }
}

std::vector<u8> File::ReadBytes(const std::streampos offset,
                                const std::streamsize numBytes) {
    if (offset < 0 || numBytes <= 0) {
        throw std::runtime_error{"Invalid offset/numBytes"};
    }

    using Char = std::ifstream::char_type;
    const auto size{static_cast<std::size_t>(numBytes)};

    this->stream.seekg(offset);
    if (!this->stream) {
        throw std::runtime_error{"Failed to seek to stream offset."};
    }

    std::vector<u8> bytes(size);
    this->stream.read(reinterpret_cast<Char*>(bytes.data()), numBytes);
    if (this->stream.gcount() != numBytes) {
        throw std::runtime_error{"Failed to read bytes from file."};
    }
    return bytes;
}

}
