#pragma once
#include <memory>
#include "instance.h"
#include "window.h"
#include "wrapper.h"

class SDL_Renderer;

namespace sdl {

class Texture;

class Renderer_;
using Renderer = std::shared_ptr<Renderer_>;

/*
 * Class wrapping an SDL renderer. Handles allocation/deallocation of associated
 * resources. Provides access to the native SDL_Renderer handle.
 */
class Renderer_ {
public:
    /*
     * Static constructor, creates a new renderer targeting the provided window.
     * Enables hardware acceleration and sets a black draw color.
     */
    static Renderer Create(Instance instance, Window window);

    /* Clears the surface managed by the renderer (i.e. draws black pixels). */
    void Clear();

    /* Copies the contents of the provided texture to the renderer's backbuffer. */
    void Copy(Texture& texture);

    /* Presents the contents of the backbuffer to the renderer's drawing surface. */
    void Present();

    /* Returns a pointer to the wrapped SDL_Renderer. */
    SDL_Renderer* Handle();
private:
    Renderer_(Instance&& instance, Window&& window);
    static void Destroy(SDL_Renderer* p);
    Instance instance;
    Window window;
    Wrapper<SDL_Renderer, Destroy> handle;
};

}
