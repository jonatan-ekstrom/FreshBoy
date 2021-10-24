#include "file.h"
#include <cstddef>

using Char = std::fstream::char_type;

namespace gb {

InputFile::InputFile(const Path& filePath)
    : stream{filePath, std::ios::binary} {
    if (!this->stream) {
        throw std::runtime_error{"InputFile - Failed to open file: " + filePath.string()};
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

    std::vector<u8> bytes(size);
    this->stream.read(reinterpret_cast<Char*>(bytes.data()), numBytes);
    if (this->stream.gcount() != numBytes) {
        throw std::runtime_error{"InputFile - Failed to read bytes."};
    }
    return bytes;
}

OutputFile::OutputFile(const Path& filePath)
    : stream{filePath, std::ios::binary} {
    if (!this->stream) {
        throw std::runtime_error{"OutputFile - Failed to open file: " + filePath.string()};
    }
}

void OutputFile::WriteBytes(const std::streampos offset, const std::vector<u8>& bytes) {
    if (offset < 0) {
        throw std::runtime_error{"OutputFile - Invalid offset."};
    }
    const auto numBytes{static_cast<std::streamsize>(bytes.size())};
    if (numBytes == 0) return;

    this->stream.seekp(offset);
    if (!this->stream) {
        throw std::runtime_error{"OutputFile - Failed to seek to stream offset."};
    }

    this->stream.write(reinterpret_cast<const Char*>(bytes.data()), numBytes);
    if (!this->stream) {
        throw std::runtime_error{"OutputFile - Failed to write bytes."};
    }
}

}
