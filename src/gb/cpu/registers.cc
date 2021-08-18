#include "registers.h"
#include "bits.h"

namespace gb {

template<typename T>
Register<T>::Register() : v{0} {}

template class Register<u8>;
template class Register<u16>;

Address::Address(const u16 a) : v{a} {}

RegPair::RegPair(ByteReg& h, ByteReg& l) : h{h.v}, l{l.v} {}

Address RegPair::Addr() { return Address{bit::Merge(this->h, this->l)}; }

void RegPair::Inc() {
    auto merged{bit::Merge(this->h, this->l)};
    ++merged;
    this->h = bit::HighByte(merged);
    this->l = bit::LowByte(merged);
}

void RegPair::Dec() {
    auto merged{bit::Merge(this->h, this->l)};
    --merged;
    this->h = bit::HighByte(merged);
    this->l = bit::LowByte(merged);
}

Flags::Flags() : Z{false}, N{false}, H{false}, C{false} {}

}
