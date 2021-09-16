#include "mbc3.h"
#include <stdexcept>
#include <utility>
#include "bits.h"
#include "file.h"
#include "header.h"
#include "log.h"

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
        case 0x0C: return this->latched.Ctrl;
        default: throw std::runtime_error{"RTC - invalid read address."};
    }
}

void Rtc::Write(const u8 address, const u8 byte) {
    switch (address) {
        case 0x08: this->curr.Sec = static_cast<u8>(byte & 0x3F); this->cycleCount = 0; break;
        case 0x09: this->curr.Min = static_cast<u8>(byte & 0x3F); break;
        case 0x0A: this->curr.Hrs = static_cast<u8>(byte & 0x1F); break;
        case 0x0B: this->curr.Days = byte; break;
        case 0x0C: this->curr.Ctrl = static_cast<u8>(byte & 0xC1); break;
        default: throw std::runtime_error{"RTC - invalid write address."};
    }
}

void Rtc::Tick(const uint cycles) {
    if (!Active()) return;

    this->cycleCount += cycles;
    if (this->cycleCount >= this->cyclesPerSecond) {
        this->cycleCount -= this->cyclesPerSecond;
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
        this->curr.Sec = static_cast<u8>((this->curr.Sec + 1) % 64);
        carry = false;
    }

    if (!carry) return;

    if (this->curr.Min == 59) {
        this->curr.Min = 0;
    } else {
        this->curr.Min = static_cast<u8>((this->curr.Min + 1) % 64);
        carry = false;
    }

    if (!carry) return;

    if (this->curr.Hrs == 23) {
        this->curr.Hrs = 0;
    } else {
        this->curr.Hrs = static_cast<u8>((this->curr.Hrs + 1) % 32);
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

MBC3::MBC3(const std::string& romPath, Header&& header, const uint refreshRate)
    : MBC{std::move(header)},
      rtc{refreshRate},
      enabled{false},
      latchPending{false},
      romBank{1},
      selector{0},
      romBitMask{0},
      ramBitMask{0} {
    constexpr auto romBankSize{0x4000};
    constexpr auto ramBankSize{0x2000};
    const auto numRomBanks{this->header.RomBanks()};
    const auto numRamBanks{this->header.RamBanks()};

    InputFile file{romPath};
    for (auto i{0u}; i < numRomBanks; ++i) {
        const auto offset{i * romBankSize};
        this->romBanks.push_back(file.ReadBytes(offset, romBankSize));
    }

    for (auto i{0u}; i < numRamBanks; ++i) {
        this->ramBanks.push_back(MemBlock(ramBankSize));
    }

    this->romBitMask = static_cast<u8>(numRomBanks - 1);
    this->ramBitMask = numRamBanks != 0 ? static_cast<u8>(numRamBanks - 1) : 0;
}

u8 MBC3::Read(const u16 address) const {
    if (address <= 0x3FFF) {
        return this->romBanks[0][address];
    }

    if (address >= 0x4000 && address <= 0x7FFF) {
        return this->romBanks[RomBank()][address - 0x4000];
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        const auto ram{RamBank()};
        const auto reg{Register()};
        if (ram) {
            return this->ramBanks[ram.value()][address - 0xA000];
        }
        if (reg) {
            return this->rtc.Read(reg.value());
        }
        log::Warning("MBC3 - Invalid RAM/RTC read: " + log::Hex(address));
        return 0xFF;
    }

    log::Warning("MBC3 - Invalid read address: " + log::Hex(address));
    return 0xFF;
}

void MBC3::Write(const u16 address, const u8 byte) {
    if (address <= 0x1FFF) {
        this->enabled = ((byte & 0x0F) == 0x0A);
        return;
    }

    if (address >= 0x2000 && address <=0x3FFF) {
        this->romBank = byte & 0x7F;
        if (this->romBank == 0) this->romBank = 1;
        return;
    }

    if (address >= 0x4000 && address <= 0x5FFF) {
        this->selector = byte;
        return;
    }

    if (address >= 0x6000 && address <= 0x7FFF) {
        if (byte == 0) {
            this->latchPending = true;
            return;
        }

        if (byte == 1 && this->latchPending) {
            this->rtc.Latch();
        }

        this->latchPending = false;
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        const auto ram{RamBank()};
        const auto reg{Register()};
        if (ram) {
            this->ramBanks[ram.value()][address - 0xA000] = byte;
            return;
        }
        if (reg) {
            this->rtc.Write(reg.value(), byte);
            return;
        }
        log::Warning("MBC3 - Invalid RAM/RTC write: " + log::Hex(address));
        return;
    }

    log::Warning("MBC3 - Invalid write address: " + log::Hex(address));
}

void MBC3::Tick(const uint cycles) {
    this->rtc.Tick(cycles);
}

uint MBC3::RomBank() const {
    return this->romBank & this->romBitMask;
}

std::optional<uint> MBC3::RamBank() const {
    if (!this->enabled || this->ramBanks.empty() || this->selector > 0x03) {
        return {};
    }

    return this->selector & this->ramBitMask;
}

std::optional<u8> MBC3::Register() const {
    if (!this->enabled || this->selector < 0x08 || this->selector > 0x0C) {
        return {};
    }
    return this->selector;
}

}
