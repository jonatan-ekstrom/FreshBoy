#pragma once
#include <cstdint>
#include "interrupt.h"

namespace gb {

class Serial {
public:
    explicit Serial(InterruptManager interrupts);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Tick(unsigned int cycles);
private:
    bool TransferInProgress() const;
    void ScWrite(std::uint8_t byte);
    void StartTransfer();
    void Shift();
    void TransferDone();
    InterruptManager interrupts;
    std::uint8_t sb;
    std::uint8_t sc;
    unsigned int cycleCount;
    unsigned int shifts;
};

}
