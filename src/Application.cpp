
#include <SDL2/SDL.h>

#include "Application.hpp"

Application::Application(const char* name)
  : Dispatcher(name)
{
    config.setString("application title", name);
    config.setNumber("application width", 640);
    config.setNumber("application height", 480);
}

Application::~Application() {
    // empty
}
