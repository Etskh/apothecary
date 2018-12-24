#ifndef _INCLUDE_SDLDEVICE_HPP
#define _INCLUDE_SDLDEVICE_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../core/Logger.hpp"
#include "../TDevice.hpp"
#include "../Font.hpp"
#include "../Application.hpp"
#include "SDLRenderable.hpp"


class SDLDevice: public TDevice<SDLRenderable> {
public:
    SDLDevice(Application& app);
    virtual ~SDLDevice();

    virtual bool init(const DataEntry& config);
    virtual int run();
    virtual void render(float delta);

    virtual Font::smrtptr createFont(const char* fontName);

    virtual Renderable createRenderableTexture(
        Texture::smrtptr tex, int x, int y, int w, int h);

private:
    std::vector<Font::smrtptr> fontResources;
    Logger logger;
    Application& _app;
    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif /* end of include guard: _INCLUDE_SDLDEVICE_HPP */
