#pragma once
#include <cstdint>
#include <vector>
#include "instance.h"

namespace sdl {

class Audio {
public:
    using Samples = std::vector<std::uint8_t>;
    explicit Audio(Instance instance);
    ~Audio();
    void Queue(const Samples& left, const Samples& right);
    void Play();
    void Pause();
private:
    Instance instance;
    std::uint32_t id;
};

}
