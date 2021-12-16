#pragma once
#include <cstdint>
#include "instance.h"
#include "renderer.h"
#include "wrapper.h"

struct SDL_Texture;

namespace sdl {

/*
 * Class wrapping an SDL texture. Handles allocation/deallocation of associated
 * resources. Provides access to the native SDL_Texture handle.
 */
class Texture {
public:
    /*
     * Creates a new texture associated with the provided renderer.
     */
    Texture(Instance instance, Renderer renderer, int width, int height);

    /* Returns the width of the texture in pixels. */
    int Width() const;

    /* Returns the height of the texture in pixels. */
    int Height() const;

    /* Locks the texture and returns a pointer for modifying pixel data. */
    std::uint32_t* Lock();

    /* Unlocks the texture and commits all modifications. */
    void Unlock();

    /* Returns a pointer to the wrapped SDL_Texture. */
    SDL_Texture* Handle();
private:
    static void Destroy(SDL_Texture* p);
    Instance instance;
    Renderer renderer;
    int width;
    int height;
    Wrapper<SDL_Texture, Destroy> handle;
};

}
