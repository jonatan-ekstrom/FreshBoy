#pragma once
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include "types.h"

namespace gb {

class File {
public:
    explicit File(const std::string& filePath);
    std::vector<u8> ReadBytes(std::streampos offset, std::streamsize numBytes);
private:
    std::ifstream stream;
};

}
