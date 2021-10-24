#pragma once
#include <fstream>
#include <ios>
#include <vector>
#include "path.h"
#include "types.h"

namespace gb {

class InputFile {
public:
    explicit InputFile(const Path& filePath);
    std::vector<u8> ReadBytes(std::streampos offset, std::streamsize numBytes);
private:
    std::ifstream stream;
};

class OutputFile {
public:
    explicit OutputFile(const Path& filePath);
    void WriteBytes(std::streampos offset, const std::vector<u8>& bytes);
private:
    std::ofstream stream;
};

}
