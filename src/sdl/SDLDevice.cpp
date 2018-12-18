
#include "SDLDevice.hpp"
#include "SDLFont.hpp"

SDLDevice::SDLDevice()
    : TDevice()
    , window(nullptr)
    , renderer(nullptr)
    , logger("SDLDevice")
{
    // empty
}

SDLDevice::~SDLDevice() {
    if( renderer != nullptr ) {
        logger.info("Shutting down renderer");
        SDL_DestroyRenderer(renderer);
    }
    if( window != nullptr ) {
        logger.info("Shutting down window");
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool SDLDevice::init(const DataEntry& config) {

    logger.info("Initiaizing renderer");

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        //SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        logger.error("Unable to initialize SDL");
        return false;
    }

    logger.info("TODO: Print out graphics specs");

    if (TTF_Init() != 0) {
        logger.error("Unable to initialize TTF");
        return false;
    }

    logger.info("Initialized TTF fonts");


    const char* title = config.getString("application title");
    int width = config.getNumber("application width");
    int height = config.getNumber("application height");
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr){
        logger.error("SDL_CreateWindow error");
        // std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    logger.info("Initialized window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        logger.error("SDL_CreateRenderer error");
    	// std::cout << "SDL_CreataeRenderer Error: " << SDL_GetError() << std::endl;
    	return false;
    }
    logger.info("Initialized renderer");

    // SDL_SetRenderDrawColor(renderer, 123, 180, 230, 255);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 140);

    return true;
}

int SDLDevice::run() {
    bool isRunning = true;
    float delta = 0.016 * 1000;
    SDL_Event event;
    while(isRunning) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }

    	this->render(delta);
    }

    return 0;
}


void SDLDevice::render(float delta) {
    //First clear the renderer
    SDL_RenderClear(renderer);
    //Draw the texture
    // SDL_RenderCopy(ren, tex, NULL, NULL);
    //_renderList[0]->render(0, 0, 200, 80);
    for( auto it = _renderables.begin(); it != _renderables.end(); ++it) {
        SDLRenderable& renderable = it->second;
        if( !renderable.texture ) {
            continue;
        }
        // SDL_QueryTexture(_texture, NULL, NULL, &texW, &texH);
        SDL_Rect rect = {
            renderable.xPos,
            renderable.yPos,
            renderable.width,
            renderable.height
        };
        SDL_RenderCopy(renderer, renderable.texture->getHandle(), NULL, &rect);
    }
    //Update the screen
    SDL_RenderPresent(renderer);
    //Take a quick break after all that hard work
    SDL_Delay(delta);
}


Font::smrtptr SDLDevice::createFont(const char* fontName) {
    Font::smrtptr font = Font::smrtptr( new SDLFont(renderer, fontName));
    fontResources.push_back(font);
    logger.info("Font created {}", fontName);
    return font;
}


Renderable SDLDevice::createRenderableTexture(
    Texture::smrtptr tex, int x, int y, int w, int h) {
    SDLRenderable renderable = SDLRenderable(tex, x, y, w, h);
    return createRenderable(renderable);
}
