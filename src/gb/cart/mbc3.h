#pragma once
#include <ios>
#include <filesystem>
#include <optional>
#include <vector>
#include "mbc.h"
#include "types.h"

namespace gb {

class Header;
class InputFile;
class OutputFile;

class Rtc {
public:
    explicit Rtc(uint refreshRate);
    u8 Read(u8 address) const;
    void Write(u8 address, u8 byte);
    void Tick(uint cycles);
    void Latch();
    const static uint SerialSize;
    std::vector<u8> Serialize() const;
    void Deserialize(const std::vector<u8>& bytes);
private:
    struct Regs {
        u8 Sec;
        u8 Min;
        u8 Hrs;
        u8 Days;
        u8 Ctrl;
    };
    bool Active() const;
    void Tick();
    uint cyclesPerSecond;
    uint cycleCount;
    Regs curr;
    Regs latched;
};

class MBC3 final : public MBC {
public:
    MBC3(const std::filesystem::path& romPath, Header&& header, uint refreshRate);
    u8 Read(u16 address) const override;
    void Write(u16 address, u8 byte) override;
    void Tick(uint cycles) override;
private:
    void LoadHook(InputFile& file, std::streampos offset) override final;
    void SaveHook(OutputFile& file, std::streampos offset) override final;
    uint RomBank() const;
    std::optional<uint> RamBank() const;
    std::optional<u8> Register() const;
    Rtc rtc;
    bool enabled;
    bool latchPending;
    u8 romBank;
    u8 selector;
};

}
