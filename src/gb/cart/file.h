#pragma once
#include <cstdint>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

namespace gb {

class File {
public:
    explicit File(const std::string& filePath);
    std::vector<std::uint8_t> ReadBytes(std::streampos offset, std::streamsize numBytes);
private:
    std::ifstream stream;
};

}
