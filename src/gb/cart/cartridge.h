#pragma once
#include <memory>
#include <string>
#include <vector>
#include "header.h"
#include "path.h"
#include "types.h"

namespace gb {

class Cartridge_;
using Cartridge = std::shared_ptr<Cartridge_>;

/* Base class for Game Boy cartridges. */
class Cartridge_ {
public:
    /* Static factory method, creates a new cartridge from the provided ROM. */
    static Cartridge Create(const Path& romPath);

    virtual ~Cartridge_() = default;

    /* Returns a pretty printable version of the ROM header. */
    std::string HeaderInfo() const;

    /* Reads a byte from the provided address. */
    virtual u8 Read(u16 address) const = 0;

    /* Writes a byte to the provided address. */
    virtual void Write(u16 address, u8 byte) = 0;

    /* Steps the cartridge emulation the provided number of cycles. */
    virtual void Tick(uint cycles);

    /* Loads cartridge RAM from the provided file. */
    virtual void LoadRam(const Path& ramPath);

    /* Saves cartridge RAM to the provided file. */
    virtual void SaveRam(const Path& ramPath);
protected:
    using MemBlock = std::vector<u8>;
    explicit Cartridge_(Header&& header);
    Header header;
private:
    virtual u16 Checksum() const = 0;
};

}
