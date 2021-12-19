#pragma once
#include <ios>
#include <vector>
#include "cartridge.h"
#include "path.h"

namespace gb {

class Header;
class InputFile;
class OutputFile;

/* Base class for MBC cartridges. */
class MBC : public Cartridge_ {
public:
    void LoadRam(const Path& ramPath) final;
    void SaveRam(const Path& ramPath) final;
protected:
    MBC(const Path& romPath, Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
    u8 romBitMask;
    u8 ramBitMask;
private:
    u16 Checksum() const final;
    virtual void LoadHook(InputFile& file, std::streampos offset);
    virtual void SaveHook(OutputFile& file, std::streampos offset);
};

}
