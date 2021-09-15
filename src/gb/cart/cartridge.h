#pragma once
#include <memory>
#include <string>
#include <vector>
#include "header.h"
#include "types.h"

namespace gb {

class Cartridge_;
using Cartridge = std::shared_ptr<Cartridge_>;

class Cartridge_ {
public:
    static Cartridge Create(const std::string& filePath);
    virtual ~Cartridge_() = default;
    std::string HeaderInfo() const;
    virtual u8 Read(u16 address) const = 0;
    virtual void Write(u16 address, u8 byte) = 0;
    virtual void Tick(uint cycles);
protected:
    using MemBlock = std::vector<u8>;
    explicit Cartridge_(Header&& header);
    Header header;
private:
    virtual u16 Checksum() const = 0;
};

}
