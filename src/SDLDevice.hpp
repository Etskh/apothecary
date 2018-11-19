#ifndef _INCLUDE_SDLDEVICE_HPP
#define _INCLUDE_SDLDEVICE_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Device.hpp"
#include "Font.hpp"
#include "Logger.hpp"


class SDLDevice: public Device {
public:
    SDLDevice();
    virtual ~SDLDevice();

    virtual bool init(const DataEntry& config);
    virtual void render(float delta);

    virtual Font::smrtptr createFont(const char* fontName);

private:
    std::vector<Font::smrtptr> fontResources;
    Logger logger;
    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif /* end of include guard: _INCLUDE_SDLDEVICE_HPP */
