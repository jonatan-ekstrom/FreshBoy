#pragma once
#include <cstdint>
#include <memory>
#include "interrupt.h"
#include "types.h"

namespace gb {

class Serial_;
using Serial = std::shared_ptr<Serial_>;

class Serial_ {
public:
    static Serial Create(InterruptManager interrupts);
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
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
    uint cycleCount;
    uint shifts;
};

}
