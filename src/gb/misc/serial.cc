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

Serial_::Serial_(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      sb{0},
      sc{0},
      cycleCount{0},
      shifts{0} {}

Serial Serial_::Create(InterruptManager interrupts) {
    return Serial{new Serial_{std::move(interrupts)}};
}

std::uint8_t Serial_::Read(const std::uint16_t address) const {
    if (address == SbAddress) return this->sb;
    if (address == ScAddress) return this->sc;
    throw std::runtime_error{"Serial - invalid read address."};
}

void Serial_::Write(const std::uint16_t address, const std::uint8_t byte) {
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

void Serial_::Tick(const unsigned int cycles) {
    constexpr auto divider{512};
    this->cycleCount += cycles;
    const auto numShifts{this->cycleCount / divider};
    this->cycleCount %= divider;
    for (auto i{0u}; TransferInProgress() && i < numShifts; ++i) {
        Shift();
    }
}

bool Serial_::TransferInProgress() const {
    return this->sc == 0x81;
}

void Serial_::ScWrite(const std::uint8_t byte) {
    this->sc = byte & 0x81;
    if (this->sc == 0x81) {
        StartTransfer();
    }
}

void Serial_::StartTransfer() {
    this->shifts = 0;
}

void Serial_::Shift() {
    this->sb = static_cast<uint8_t>((this->sb << 1) | 1);
    if (this->shifts++ == 8) {
        TransferDone();
    }
}

void Serial_::TransferDone() {
    ClearBit(this->sc, 7);
    this->shifts = 0;
    this->interrupts->RequestInterrupt(Interrupt::Serial);
}

}
