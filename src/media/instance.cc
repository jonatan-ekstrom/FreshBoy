#include "instance.h"
#include <stdexcept>
#include <SDL.h>
#include <SDL_error.h>

namespace sdl {

Instance_::Instance_() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error{SDL_GetError()};
   }
}

Instance_::~Instance_() {
   SDL_Quit();
}

Instance Instance_::Create() {
    return Instance{new Instance_};
}

}
