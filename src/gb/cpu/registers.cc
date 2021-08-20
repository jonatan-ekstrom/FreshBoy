#include "registers.h"
#include "bits.h"

namespace gb {

template<typename T>
Register<T>::Register() : v{0} {}

template<typename T> template<typename U>
Addr<U> Register<T>::IoAddr() const { return static_cast<u16>(0xFF00 + this->v); }

template class Register<u8>;
template class Register<u16>;

Address::Address(const u16 a) : a{a} {}

RegPair::RegPair(ByteReg& h, ByteReg& l) : h{h.v}, l{l.v} {}

u16 RegPair::Addr() { return bit::Merge(this->h, this->l); }

void RegPair::Inc() {
    auto merged{bit::Merge(this->h, this->l)};
    ++merged;
    this->h = bit::High(merged);
    this->l = bit::Low(merged);
}

void RegPair::Dec() {
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
