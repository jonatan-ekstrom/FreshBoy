#include "mbc3.h"
#include <stdexcept>
#include "bits.h"

namespace { constexpr auto CyclesPerFrame{70224}; }

namespace gb {

Rtc::Rtc(const uint refreshRate)
    : cyclesPerSecond{CyclesPerFrame * refreshRate},
      cycleCount{0},
      curr{},
      latched{} {}

u8 Rtc::Read(const u8 address) const {
    switch (address) {
        case 0x08: return this->latched.Sec;
        case 0x09: return this->latched.Min;
        case 0x0A: return this->latched.Hrs;
        case 0x0B: return this->latched.Days;
        case 0x0C: return static_cast<u8>(this->latched.Ctrl | 0x3E);
        default: throw std::runtime_error{"RTC - invalid read address."};
    }
}

void Rtc::Write(const u8 address, const u8 byte) {
    switch (address) {
        case 0x08: this->curr.Sec = byte <= 59 ? byte : 59; break;
        case 0x09: this->curr.Min = byte <= 59 ? byte : 59; break;
        case 0x0A: this->curr.Hrs = byte <= 23 ? byte : 23; break;
        case 0x0B: this->curr.Days = byte; break;
        case 0x0C: this->curr.Ctrl = static_cast<u8>(byte & 0xC1); break;
        default: throw std::runtime_error{"RTC - invalid write address."};
    }
}

void Rtc::Tick(const uint cycles) {
    this->cycleCount += cycles;
    if (this->cycleCount < this->cyclesPerSecond) return;

    this->cycleCount -= this->cyclesPerSecond;
    if (Active()) {
        Tick();
    }
}

void Rtc::Latch() {
    this->latched = this->curr;
}

bool Rtc::Active() const {
    return bit::IsClear(this->curr.Ctrl, 6);
}

void Rtc::Tick() {
    bool carry;
    if (this->curr.Sec == 59) {
        this->curr.Sec = 0;
        carry = true;
    } else {
        ++this->curr.Sec;
        carry = false;
    }

    if (!carry) return;

    if (this->curr.Min == 59) {
        this->curr.Min = 0;
    } else {
        ++this->curr.Min;
        carry = false;
    }

    if (!carry) return;

    if (this->curr.Hrs == 23) {
        this->curr.Hrs = 0;
    } else {
        ++this->curr.Hrs;
        carry = false;
    }

    if (!carry) return;

    auto days{((this->curr.Ctrl & 0x01) << 8) | this->curr.Days};
    if (days == 511) {
        this->curr.Days = 0;
        bit::Clear(this->curr.Ctrl, 0);
        bit::Set(this->curr.Ctrl, 7);
    } else {
        ++days;
        this->curr.Days = static_cast<u8>(days & 0xFF);
        bit::Update(this->curr.Ctrl, 0, bit::IsSet(days, 8));
    }
}

}
