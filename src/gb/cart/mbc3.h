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

/* MBC3 Real Time Clock. */
class Rtc {
public:
    using State = std::array<u8, 9>;
    /* Initialize a new real-time clock for the provided screen refresh rate. */
    explicit Rtc(uint refreshRate);

    /* Read data from the provided address. */
    u8 Read(u8 address) const;

    /* Write data to the provided address. */
    void Write(u8 address, u8 byte);

    /* Tick the clock the provided number of cycles. */
    void Tick(uint cycles);

    /* Latch the clock state. */
    void Latch();

    /* Serialize the internal state. */
    State Serialize() const;

    /* Deserialize the provided state. */
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

/* Handler class for MBC3 based cartridges. */
class MBC3 final : public MBC {
public:
    /* Creates a new MBC3 handler for the provided file. */
    MBC3(const Path& romPath, Header&& header, uint refreshRate);

    u8 Read(u16 address) const override;

    void Write(u16 address, u8 byte) override;

    void Tick(uint cycles) override;
private:
    void LoadHook(InputFile& file, std::streampos offset) final;
    void SaveHook(OutputFile& file, std::streampos offset) final;
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
