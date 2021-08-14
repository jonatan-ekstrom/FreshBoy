#include "serial.h"
#include <stdexcept>
#include <utility>

namespace {

constexpr auto SbAddress{0xFF01};
constexpr auto ScAddress{0xFF02};

constexpr void ClearBit(std::uint8_t& reg, const unsigned int bit) {
    reg = static_cast<std::uint8_t>(reg & ~(1 << bit));
}

}

namespace gb {

Serial::Serial(InterruptManager interrupts)
    : interrupts{std::move(interrupts)},
      sb{0},
      sc{0},
      cycleCount{0},
      shifts{0} {}

std::uint8_t Serial::Read(const std::uint16_t address) const {
    if (address == SbAddress) return this->sb;
    if (address == ScAddress) return this->sc;
    throw std::runtime_error{"Serial - invalid read address."};
}

void Serial::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == SbAddress) {
        this->sb = byte;
        return;
    }

    if (address == ScAddress) {
        ScWrite(byte);
        return;
    }

    throw std::runtime_error{"Serial - invalid write address."};
}

void Serial::Tick(const unsigned int cycles) {
    constexpr auto divider{512};
    this->cycleCount += cycles;
    const auto numShifts{this->cycleCount / divider};
    this->cycleCount %= divider;
    for (auto i{0u}; TransferInProgress() && i < numShifts; ++i) {
        Shift();
    }
}

bool Serial::TransferInProgress() const {
    return this->sc == 0x81;
}

void Serial::ScWrite(const std::uint8_t byte) {
    this->sc = byte & 0x81;
    if (this->sc == 0x81) {
        StartTransfer();
    }
}

void Serial::StartTransfer() {
    this->shifts = 0;
}

void Serial::Shift() {
    this->sb = static_cast<uint8_t>(this->sb << 1);
    if (this->shifts++ == 8) {
        TransferDone();
    }
}

void Serial::TransferDone() {
    ClearBit(this->sc, 7);
    this->shifts = 0;
    this->interrupts->RequestInterrupt(Interrupt::Serial);
}

}
