#pragma once
#include <fstream>
#include <ios>
#include <vector>
#include "path.h"
#include "types.h"

namespace gb {

/* Class used to read data from a file. */
class InputFile {
public:
    /* Opens the provided file path for reading. */
    explicit InputFile(const Path& filePath);

    /* Reads numBytes from the opened file, starting at offset. */
    std::vector<u8> ReadBytes(std::streampos offset, std::streamsize numBytes);
private:
    std::ifstream stream;
};

/* Class used to write data to a file. */
class OutputFile {
public:
    /* Opens the provided file path for writing. */
    explicit OutputFile(const Path& filePath);

    /* Writes the provided vector of bytes to the opened file, starting at offset. */
    void WriteBytes(std::streampos offset, const std::vector<u8>& bytes);
private:
    std::ofstream stream;
};

}
