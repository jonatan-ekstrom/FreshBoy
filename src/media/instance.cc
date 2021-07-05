#include "instance.h"
#include <stdexcept>
#include <SDL.h>
#include <SDL_error.h>

namespace sdl {

Inst::Inst() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error{SDL_GetError()};
   }
}

Inst::~Inst() {
   SDL_Quit();
}

Instance Inst::Create() {
    return Instance{new Inst};
}

}
