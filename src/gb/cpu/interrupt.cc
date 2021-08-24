#include "interrupt.h"
#include <stdexcept>
#include "bits.h"

namespace {

constexpr auto FlagsAddress{0xFF0F};
constexpr auto EnableAddress{0xFFFF};

}

namespace gb {

InterruptManager_::InterruptManager_() : ime{false}, flags{0}, enabled{0} {}

InterruptManager InterruptManager_::Create() {
    return InterruptManager{new InterruptManager_{}};
}

u8 InterruptManager_::Read(const u16 address) const {
    if (address == FlagsAddress) {
        return this->flags;
    }

    if (address == EnableAddress) {
        return this->enabled;
    }

    throw std::runtime_error{"InterruptManager - invalid read address."};
}

void InterruptManager_::Write(const u16 address, const u8 byte) {
    if (address == FlagsAddress) {
        this->flags = byte & 0x1F;
        return;
    }

    if (address == EnableAddress) {
        this->enabled = byte & 0x1F;
        return;
    }

    throw std::runtime_error{"InterruptManager - invalid write address."};
}

std::vector<Interrupt> InterruptManager_::PendingInterrupts() const {
    std::vector<Interrupt> pending;
    constexpr auto numInterrupts{5};
    const auto masked{static_cast<u8>(this->enabled & this->flags)};
    for (auto i{0u}; i < numInterrupts; ++i) {
        if (bit::IsSet(masked, i)) {
            pending.push_back(static_cast<Interrupt>(i));
        }
    }
    return pending;
}

bool InterruptManager_::InterruptsEnabled() const {
    return this->ime;
}

void InterruptManager_::EnableInterrupts() {
    this->ime = true;
}

void InterruptManager_::DisableInterrupts() {
    this->ime = false;
}

void InterruptManager_::RequestInterrupt(const Interrupt intr) {
    bit::Set(this->flags, static_cast<uint>(intr));
}

void InterruptManager_::AcknowledgeInterrupt(const Interrupt intr) {
    bit::Clear(this->flags, static_cast<uint>(intr));
}

}
