#include "registers.h"
#include "bits.h"

namespace gb {

ByteReg::ByteReg() : v{0} {}

Address ByteReg::Addr() const { return Address{static_cast<u16>(0xFF00 + this->v)}; }

WordReg::WordReg() : v{0} {}

Address::Address(const u16 a) : a{a} {}
Address::Address(const u8 a) : a{static_cast<u16>(a + 0xFF00)} {}

RegPair::RegPair(ByteReg& h, ByteReg& l) : h{h.v}, l{l.v} {}

u16 RegPair::Addr() const { return bit::Merge(this->h, this->l); }

void RegPair::Inc() const {
    auto merged{bit::Merge(this->h, this->l)};
    ++merged;
    this->h = bit::High(merged);
    this->l = bit::Low(merged);
}

void RegPair::Dec() const {
    auto merged{bit::Merge(this->h, this->l)};
    --merged;
    this->h = bit::High(merged);
    this->l = bit::Low(merged);
}

Flags::Flags(ByteReg& f) : f{f.v} {}

bool Flags::Z() const { return bit::IsSet(this->f, 7); }

bool Flags::N() const { return bit::IsSet(this->f, 6); }

bool Flags::H() const { return bit::IsSet(this->f, 5); }

bool Flags::C() const { return bit::IsSet(this->f, 4); }

void Flags::UpdateZ(const bool set) { bit::Update(this->f, 7, set); }

void Flags::UpdateN(const bool set) { bit::Update(this->f, 6, set); }

void Flags::UpdateH(const bool set) { bit::Update(this->f, 5, set); }

void Flags::UpdateC(const bool set) { bit::Update(this->f, 4, set); }

}
