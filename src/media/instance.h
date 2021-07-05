#pragma once
#include <memory>

namespace sdl {

class Inst;
using Instance = std::shared_ptr<const Inst>;

class Inst {
public:
    ~Inst();
    Inst(const Inst&) = delete;
    Inst& operator=(const Inst&) = delete;
    static Instance Create();
private:
    Inst();
};

}
