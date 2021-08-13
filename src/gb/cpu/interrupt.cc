#include "interrupt.h"
#include <stdexcept>

namespace {

constexpr auto FlagsAddress{0xFF0F};
constexpr auto EnableAddress{0xFFFF};

constexpr bool BitSet(const std::uint8_t reg, const unsigned int bit) {
    return (reg & (1 << bit)) != 0;
}

constexpr void SetBit(std::uint8_t& reg, const unsigned int bit) {
    reg = static_cast<uint8_t>(reg | (1 << bit));
}

constexpr void ClearBit(std::uint8_t& reg, const unsigned int bit) {
    reg = static_cast<uint8_t>(reg & ~(1 << bit));
}

}

namespace gb {

InterruptManager::InterruptManager() : ime{false}, flags{0}, enabled{0} {}

std::uint8_t InterruptManager::Read(const std::uint16_t address) const {
    if (address == FlagsAddress) {
        return this->flags;
    }

    if (address == EnableAddress) {
        return this->enabled;
    }

    throw std::runtime_error{"InterruptManager - invalid read address."};
}

void InterruptManager::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == FlagsAddress) {
        this->flags = byte & 0x1F;
    }

    if (address == EnableAddress) {
        this->enabled = byte & 0x1F;
    }

    throw std::runtime_error{"InterruptManager - invalid write address."};
}

std::vector<Interrupt> InterruptManager::PendingInterrupts() const {
    if (!this->ime) {
        return {};
    }

    std::vector<Interrupt> pending;
    constexpr auto numInterrupts{5};
    const auto masked{static_cast<std::uint8_t>(this->enabled & this->flags)};
    for (auto i{0u}; i < numInterrupts; ++i) {
        if (BitSet(masked, i)) {
            pending.push_back(static_cast<Interrupt>(i));
        }
    }
    return pending;
}

void InterruptManager::EnableInterrupts() {
    this->ime = true;
}

void InterruptManager::DisableInterrupts() {
    this->ime = false;
}

void InterruptManager::RequestInterrupt(const Interrupt intr) {
    SetBit(this->flags, static_cast<unsigned int>(intr));
}

void InterruptManager::AcknowledgeInterrupt(const Interrupt intr) {
    ClearBit(this->flags, static_cast<unsigned int>(intr));
}

}
