#pragma once
#include "types.h"

namespace gb {

class Channel4 {
public:
    Channel4();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
private:
    u8 nr41;
    u8 nr42;
    u8 nr43;
    u8 nr44;
};

}
