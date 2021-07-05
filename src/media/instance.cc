#include "instance.h"
#include <stdexcept>
#include <SDL.h>
#include <SDL_error.h>

namespace sdl {

Instance::Instance() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error{SDL_GetError()};
   }
}

Instance::~Instance() {
   SDL_Quit();
}

}
