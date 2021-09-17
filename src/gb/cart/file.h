#pragma once
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>
#include "types.h"

namespace gb {

class InputFile {
public:
    explicit InputFile(const std::filesystem::path& filePath);
    std::vector<u8> ReadBytes(std::streampos offset, std::streamsize numBytes);
private:
    std::ifstream stream;
};

class OutputFile {
public:
    explicit OutputFile(const std::filesystem::path& filePath);
    void WriteBytes(std::streampos offset, const std::vector<u8>& bytes);
private:
    std::ofstream stream;
};

}
