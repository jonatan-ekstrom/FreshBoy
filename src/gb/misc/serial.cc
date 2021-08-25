#include "serial.h"
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
      cycleCount{0},
      shifts{0} {}

Serial Serial_::Create(InterruptManager interrupts) {
    return Serial{new Serial_{std::move(interrupts)}};
}

u8 Serial_::Read(const u16 address) const {
    if (address == SbAddress) return this->sb;
    if (address == ScAddress) return this->sc;
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
    for (auto i{0u}; TransferInProgress() && i < numShifts; ++i) {
        Shift();
    }
}

bool Serial_::TransferInProgress() const {
    return this->sc == 0x81;
}

void Serial_::ScWrite(const u8 byte) {
    this->sc = byte & 0x81;
    if (this->sc == 0x81) {
        StartTransfer();
    }
}

void Serial_::StartTransfer() {
    this->shifts = 0;
}

void Serial_::Shift() {
    this->sb = static_cast<u8>((this->sb << 1) | 1);
    if (this->shifts++ == 8) {
        TransferDone();
    }
}

void Serial_::TransferDone() {
    bit::Clear(this->sc, 7);
    this->shifts = 0;
    this->interrupts->RequestInterrupt(Interrupt::Serial);
}

}
