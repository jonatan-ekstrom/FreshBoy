#include "audio.h"
#include <stdexcept>
#include <utility>
#include <SDL_audio.h>
#include <SDL_error.h>

namespace sdl {

Audio::Audio(Instance instance)
    : instance{std::move(instance)} {
    /*
     * Setup the desired audio format.
     * We're using 44.1 kHz stereo sound in 8-bit unsigned samples.
     */
    SDL_AudioSpec desired{}, obtained{};
    desired.freq = 44100;
    desired.format = AUDIO_U8;
    desired.channels = 2;
    desired.samples = 1024;

    this->id = SDL_OpenAudioDevice(nullptr, 0, &desired, &obtained, 0);
    if (this->id == 0) {
        throw std::runtime_error{SDL_GetError()};
    }
}

void Audio::Queue(const Samples& left, const Samples& right) {
    if (left.size() != right.size()) {
        throw std::runtime_error{"Audio - left/right channel size mismatch."};
    }

    /*
     * Left and right channel audio samples are interleaved.
     * LRLRLRLRLRLRLR ...
     */
    const auto size{static_cast<unsigned int>(left.size())};
    Samples samples(2 * size);
    for (auto i{0u}; i < size; ++i) {
        samples[2 * i] = left[i];
        samples[2 * i + 1] = right[i];
    }

    if (SDL_QueueAudio(this->id, samples.data(), 2 * size) != 0) {
        throw std::runtime_error{SDL_GetError()};
    }
}

void Audio::Play() {
    SDL_PauseAudioDevice(this->id, 0);
}

Audio::~Audio() {
    if (this->id != 0) {
        SDL_CloseAudioDevice(this->id);
    }
}

Audio::Audio(Audio&& other) noexcept : id{0} {
    Swap(*this, other);
}

Audio& Audio::operator=(Audio&& other) noexcept {
    Swap(*this, other);
    return *this;
}

void Swap(Audio& lhs, Audio& rhs) noexcept {
    using std::swap;
    swap(lhs.instance, rhs.instance);
    swap(lhs.id, rhs.id);
}

}
