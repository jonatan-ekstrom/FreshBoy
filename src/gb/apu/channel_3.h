#pragma once
#include <array>
#include "types.h"

namespace gb {

class Channel3 {
public:
    Channel3();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
private:
    u8 nr30;
    u8 nr31;
    u8 nr32;
    u8 nr33;
    u8 nr34;
    std::array<u8, 16> wave;
};

}
