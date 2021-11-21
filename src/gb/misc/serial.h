#pragma once
#include <memory>
#include "interrupt.h"
#include "types.h"

namespace gb {

class Serial_;
using Serial = std::shared_ptr<Serial_>;

/* Class representing the serial port component. */
class Serial_ {
public:
    /* Static constructor. */
    static Serial Create(InterruptManager interrupts);

    /* Read state. */
    u8 Read(u16 address) const;

    /* Write state */
    void Write(u16 address, u8 byte);

    /* Step serial component the provided number of cycles. */
    void Tick(uint cycles);
private:
    explicit Serial_(InterruptManager&& interrupts);
    bool TransferInProgress() const;
    void ScWrite(u8 byte);
    void StartTransfer();
    void Shift();
    void TransferDone();
    InterruptManager interrupts;
    u8 sb;
    u8 sc;
    u8 out;
    uint cycleCount;
    uint shifts;
};

}
