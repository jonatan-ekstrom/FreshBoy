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
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Tick(uint cycles);
private:
    explicit Serial_(InterruptManager&& interrupts);
    bool TransferInProgress() const;
    void ScWrite(std::uint8_t byte);
    void StartTransfer();
    void Shift();
    void TransferDone();
    InterruptManager interrupts;
    std::uint8_t sb;
    std::uint8_t sc;
    uint cycleCount;
    uint shifts;
};

}
