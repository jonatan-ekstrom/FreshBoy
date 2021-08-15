#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "types.h"

namespace gb {

enum class Interrupt {
    VBlank,
    Stat,
    Timer,
    Serial,
    Joypad
};

class InterruptManager_;
using InterruptManager = std::shared_ptr<InterruptManager_>;

class InterruptManager_ {
public:
    static InterruptManager Create();
    u8 Read(std::uint16_t address) const;
    void Write(std::uint16_t address, u8 byte);
    std::vector<Interrupt> PendingInterrupts() const;
    void EnableInterrupts();
    void DisableInterrupts();
    void RequestInterrupt(Interrupt intr);
    void AcknowledgeInterrupt(Interrupt intr);
private:
    InterruptManager_();
    bool ime;
    u8 flags;
    u8 enabled;
};

}
