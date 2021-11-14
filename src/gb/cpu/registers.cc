#include "registers.h"
#include <stdexcept>
#include "bits.h"

namespace gb {

Imm16 Base8::IO() const { return Imm16{static_cast<u16>(0xFF00 + this->v)}; }

u16 Base16::Ptr() const { return this->v; }

RegPair::RegPair(ByteReg& h, ByteReg& l) : h{h.v}, l{l.v} {}

u16 RegPair::Ptr() const { return bit::Merge(this->h, this->l); }

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

bool Flags::Check(const Condition c) const {
    switch (c) {
        case Condition::NZ: return !Z();
        case Condition::Z: return Z();
        case Condition::NC: return !C();
        case Condition::C: return C();
        default: throw std::runtime_error{"Flags - Unknown condition."};
    }
}

bool Flags::Z() const { return bit::IsSet(this->f, 7); }

bool Flags::N() const { return bit::IsSet(this->f, 6); }

bool Flags::H() const { return bit::IsSet(this->f, 5); }

bool Flags::C() const { return bit::IsSet(this->f, 4); }

void Flags::UpdateZ(const bool set) { bit::Update(this->f, 7, set); }

void Flags::UpdateN(const bool set) { bit::Update(this->f, 6, set); }

void Flags::UpdateH(const bool set) { bit::Update(this->f, 5, set); }

void Flags::UpdateC(const bool set) { bit::Update(this->f, 4, set); }

}
