#include "serial.h"
#include <iostream>
#include <utility>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto SbAddress{0xFF01};
constexpr auto ScAddress{0xFF02};

}

namespace gb {

Serial_::Serial_(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      sb{0},
      sc{0},
      out{0},
      cycleCount{0},
      shifts{0} {}

Serial Serial_::Create(InterruptManager interrupts) {
    return Serial{new Serial_{std::move(interrupts)}};
}

u8 Serial_::Read(const u16 address) const {
    if (address == SbAddress) return this->sb;
    if (address == ScAddress) return this->sc | 0x7C;
    log::Warning("Serial - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Serial_::Write(const u16 address, const u8 byte) {
    if (address == SbAddress) {
        this->sb = byte;
        return;
    }

    if (address == ScAddress) {
        ScWrite(byte);
        return;
    }

    log::Warning("Serial - invalid write address: " + log::Hex(address));
}

void Serial_::Tick(const uint cycles) {
    constexpr auto divider{512};
    this->cycleCount += cycles;
    const auto numShifts{this->cycleCount / divider};
    this->cycleCount %= divider;

    // Shift the registers one step per 512 ticks if a transfer is in progress.
    for (auto i{0u}; TransferInProgress() && i < numShifts; ++i) {
        Shift();
    }
}

bool Serial_::TransferInProgress() const {
    return this->sc == 0x81;
}

void Serial_::ScWrite(const u8 byte) {
    // Start transfer if 0x81 is written to the SC register.
    this->sc = byte & 0x81;
    if (this->sc == 0x81) {
        StartTransfer();
    }
}

void Serial_::StartTransfer() {
    this->shifts = 0;
}

void Serial_::Shift() {
    // Shift the MSB of SB into the LSB of the output.
    this->out = static_cast<u8>((this->out << 1) | ((this->sb & (1 << 7)) != 0));

    // Shift one into the LSB of the SB register.
    this->sb = static_cast<u8>((this->sb << 1) | 1);
    if (++this->shifts == 8) {
        TransferDone(); // Trigger interrupt after 8 shifts have been done.
    }
}

void Serial_::TransferDone() {
    bit::Clear(this->sc, 7); // Clear transfer flag.
    this->shifts = 0;
    this->interrupts->RequestInterrupt(Interrupt::Serial);
    std::cout << this->out << std::flush; // Write character to stdout.
}

}
