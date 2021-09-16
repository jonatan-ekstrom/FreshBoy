#include "file.h"
#include <cstddef>

namespace gb {

InputFile::InputFile(const std::string& filePath)
    : stream{filePath, std::ios::binary} {
    if (!this->stream) {
        throw std::runtime_error{"InputFile - Failed to open file: " + filePath};
    }
}

std::vector<u8> InputFile::ReadBytes(const std::streampos offset,
                                     const std::streamsize numBytes) {
    if (offset < 0 || numBytes <= 0) {
        throw std::runtime_error{"InputFile - Invalid offset/numBytes."};
    }

    const auto size{static_cast<std::size_t>(numBytes)};

    this->stream.seekg(offset);
    if (!this->stream) {
        throw std::runtime_error{"InputFile - Failed to seek to stream offset."};
    }

    using Char = std::fstream::char_type;
    std::vector<u8> bytes(size);
    this->stream.read(reinterpret_cast<Char*>(bytes.data()), numBytes);
    if (this->stream.gcount() != numBytes) {
        throw std::runtime_error{"InputFile - Failed to read bytes."};
    }
    return bytes;
}

}
