#pragma once
#include <array>
#include <ios>
#include <optional>
#include "mbc.h"
#include "path.h"
#include "types.h"

namespace gb {

class Header;
class InputFile;
class OutputFile;

class Rtc {
public:
    using State = std::array<u8, 9>;
    explicit Rtc(uint refreshRate);
    u8 Read(u8 address) const;
    void Write(u8 address, u8 byte);
    void Tick(uint cycles);
    void Latch();
    State Serialize() const;
    void Deserialize(const State& state);
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
    MBC3(const Path& romPath, Header&& header, uint refreshRate);
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
