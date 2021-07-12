#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "header.h"

namespace gb {

class Cartridge_;
using Cartridge = std::unique_ptr<Cartridge_>;
using MemBlock = std::vector<std::uint8_t>;

class Cartridge_ {
public:
    static Cartridge Create(const std::string& filePath);
    virtual ~Cartridge_() = default;
    std::string HeaderInfo() const;
    virtual std::uint8_t Read(std::uint16_t address) const = 0;
    virtual void Write(std::uint16_t address, std::uint8_t byte) = 0;
protected:
    explicit Cartridge_(Header&& header);
    Header header;
};

class RomOnly : public Cartridge_ {
public:
    explicit RomOnly(const std::string& filePath, Header&& header);
    uint8_t Read(std::uint16_t address) const override;
    void Write(std::uint16_t address, std::uint8_t byte) override;
private:
    MemBlock rom;
};

class MBC : public Cartridge_ {
protected:
    explicit MBC(Header&& header);
    std::vector<MemBlock> romBanks;
    std::vector<MemBlock> ramBanks;
};

class MBC1 : public MBC {
public:
    explicit MBC1(const std::string& filePath, Header&& header);
    uint8_t Read(std::uint16_t address) const override;
    void Write(std::uint16_t address, std::uint8_t byte) override;
private:
    bool RamEnabled() const;
    unsigned int RomBankLow() const;
    unsigned int RomBankHigh() const;
    unsigned int RamBank() const;
    bool AdvancedMode() const;
    std::uint8_t ramEnable;
    std::uint8_t bankLow;
    std::uint8_t bankHigh;
    std::uint8_t modeSelect;
    std::uint8_t romBitMask;
};

}