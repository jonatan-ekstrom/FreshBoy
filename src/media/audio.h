#pragma once
#include <cstdint>
#include <vector>
#include "instance.h"

namespace sdl {

/* High level API wrapper class for the SDL audio subsystem. */
class Audio {
public:
    /* The sample rate, 44.1 kHz */
    static constexpr unsigned int SampleRate{44100};

    /* A collection of samples to play. Unsigned 8-bit samples are used. */
    using Samples = std::vector<std::uint8_t>;

    /* Initializes the audio system and acquires necessary system resources. */
    explicit Audio(Instance instance);

    /*
     * Adds additional sound data to the playback queue.
     * The left and right sample collections must be of equal length.
     */
    void Queue(const Samples& left, const Samples& right);

    /* Begins playback. */
    void Play();

    ~Audio();
    Audio(const Audio&) = delete;
    Audio(Audio&& other) noexcept;
    Audio& operator=(const Audio&) = delete;
    Audio& operator=(Audio&& other) noexcept;
private:
    friend void Swap(Audio& lhs, Audio& rhs) noexcept;
    Instance instance;
    std::uint32_t id;
};

void Swap(Audio& lhs, Audio& rhs) noexcept;

}
