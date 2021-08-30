#pragma once
#include "types.h"

namespace gb {

class Channel2 {
public:
    Channel2();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Enabled() const;
    u8 Out() const;
private:
    u8 nr21;
    u8 nr22;
    u8 nr23;
    u8 nr24;
};

}
