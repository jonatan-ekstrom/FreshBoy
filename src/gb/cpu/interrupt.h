#pragma once
#include <memory>
#include <vector>
#include "types.h"

namespace gb {

/* Enumeration of supported interrupt types. */
enum class Interrupt {
    VBlank,
    Stat,
    Timer,
    Serial,
    Joypad
};

class InterruptManager_;
using InterruptManager = std::shared_ptr<InterruptManager_>;

/* Class managing interrupt handling on behalf of the CPU. */
class InterruptManager_ {
public:
    /* Static constructor. */
    static InterruptManager Create();

    /* Read byte from address. */
    u8 Read(u16 address) const;

    /* Write byte to address. */
    void Write(u16 address, u8 byte);

    /* Returns a vector of all currently pending interrupts in priority order. */
    std::vector<Interrupt> PendingInterrupts() const;

    /* Returns true if interrupts are enabled (IME is set). */
    bool InterruptsEnabled() const;

    /* Enables interrupts, i.e. sets the IME flag. */
    void EnableInterrupts();

    /* Disables interrupts, i.e. clears the IME flag. */
    void DisableInterrupts();

    /* Requests an interrupt of the provided type, i.e sets the corresponding IF flag. */
    void RequestInterrupt(Interrupt intr);

    /* Acknowledges an interrupt of the provided type, i.e. clears the corresponding IF flag. */
    void AcknowledgeInterrupt(Interrupt intr);
private:
    InterruptManager_();
    bool ime;
    u8 flags;
    u8 enabled;
};

}
