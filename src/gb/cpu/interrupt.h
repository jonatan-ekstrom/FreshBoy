#pragma once
#include <cstdint>
#include <vector>

namespace gb {

enum class Interrupt {
    VBlank,
    Stat,
    Timer,
    Serial,
    Joypad
};

class InterruptManager {
public:
    InterruptManager();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    std::vector<Interrupt> PendingInterrupts() const;
    void EnableInterrupts();
    void DisableInterrupts();
    void RequestInterrupt(Interrupt intr);
    void AcknowledgeInterrupt(Interrupt intr);
private:
    bool ime;
    std::uint8_t flags;
    std::uint8_t enabled;
};

}
