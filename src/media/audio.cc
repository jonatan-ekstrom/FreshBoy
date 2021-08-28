#include "audio.h"
#include <stdexcept>
#include <utility>
#include <SDL_audio.h>
#include <SDL_error.h>

namespace sdl {

Audio::Audio(Instance instance)
    : instance{std::move(instance)} {
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

Audio::~Audio() {
    SDL_CloseAudioDevice(this->id);
}

void Audio::Queue(const Samples& left, const Samples& right) {
    if (left.size() != right.size()) {
        throw std::runtime_error{"Audio - left/right channel size mismatch."};
    }

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

void Audio::Pause() {
    SDL_PauseAudioDevice(this->id, 1);
}

}
