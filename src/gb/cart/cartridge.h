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
protected:
    using MemBlock = std::vector<u8>;
    explicit Cartridge_(Header&& header);
    Header header;
private:
    virtual u16 Checksum() const = 0;
};

class RomOnly final : public Cartridge_ {
public:
    RomOnly(const std::string& filePath, Header&& header);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
private:
    u16 Checksum() const override;
    MemBlock rom;
};

class MBC : public Cartridge_ {
protected:
    explicit MBC(Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
};

class MBC1 final : public MBC {
public:
    MBC1(const std::string& filePath, Header&& header);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
private:
    uint RomBankLow() const;
    uint RomBankHigh() const;
    uint RamBank() const;
    u16 Checksum() const override;
    bool ramEnabled;
    bool advancedMode;
    u8 bankLow;
    u8 bankHigh;
    u8 romBitMask;
    u8 ramBitMask;
};

}
