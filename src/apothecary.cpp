#include <string>
#include <cstdio>

#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "DataEntry.hpp"
#include "Logger.hpp"
#include "Resource.hpp"
#include "Font.hpp"

#include "SDLDevice.hpp"



class Application: public SDLDevice {
public:
    Application(const char* name);
    virtual ~Application();
    int run();

private:
    Logger logger;
    bool isRunning;
    Device::smrtptr device;
    //
    DataEntry config;
};


Application::Application(const char* name)
  : logger(name)
  , isRunning(true)
  , device(nullptr)
{
    config.setString("application title", "The Apothecary");
    config.setNumber("application width", 640);
    config.setNumber("application height", 480);

    device = Device::smrtptr( new SDLDevice());
}

Application::~Application() {
    // empty
}

int Application::run() {
    logger.log("initializing");
    float delta = 0.016 * 1000;

    if( !device->init(config)) {
        return 1;
    }

    SDL_Event event;
    while(isRunning) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }
    	device->render(delta);
    }

    logger.log("shutting down");
    return 0;
}


int main(int argc, char* argv[]) {
    Application app("Apothecary");

    return app.run();
}
