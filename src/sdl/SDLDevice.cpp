
#include "../Input.hpp"
#include "SDLDevice.hpp"
#include "SDLFont.hpp"

SDLDevice::SDLDevice(Application& app)
    : TDevice()
    , logger("SDLDevice")
    , _app(app)
    , window(nullptr)
    , renderer(nullptr)
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

    int imgFlags = IMG_INIT_PNG;
    if( (IMG_Init(imgFlags) & imgFlags) != imgFlags ) {
        // printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        logger.error("Unable to load image loading");
        return false;
    }
    logger.info("Initialized image loading");

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


void SDLDevice::sendKeyEvent(SDL_Event& event, bool isPressed) {
    event::EventData keyboardData;
    auto keyevent = reinterpret_cast<SDL_KeyboardEvent*>(&event);

    // Temporarily disable repeat keys
    if( keyevent->repeat != 0 ) {
        return;
    }

    // Add the event key
    keyboardData.setNumber("code", keyevent->keysym.scancode);

    if( isPressed ) {
        _app.send(event::INPUT_KEYDOWN, keyboardData);
    }
    else {
        _app.send(event::INPUT_KEYUP, keyboardData);
    }
}


int SDLDevice::run() {
    bool isRunning = true;
    float delta = 0.016 * 1000;
    SDL_Event event;
    while(isRunning) {
        // Send the update event
        event::EventData updateData;
        _app.send(event::UPDATE, updateData);

        while (SDL_PollEvent(&event)) {
            event::EventData mouseData;

            switch(event.type) {
            case SDL_MOUSEBUTTONDOWN:
                _app.send(event::INPUT_MOUSEDOWN, mouseData);
                break;
            case SDL_MOUSEBUTTONUP:
                _app.send(event::INPUT_MOUSEUP, mouseData);
                break;
            case SDL_KEYDOWN:
                sendKeyEvent(event, true); break;
            case SDL_KEYUP:
                sendKeyEvent(event, false); break;
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }

        getCamera().update(delta);

    	this->render(delta);
    }

    return 0;
}


void SDLDevice::render(float delta) {

    SDL_SetRenderDrawColor(renderer, 117, 131, 91, 0xFF);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);

    // Draw all of the renderable objecst
    for( auto it = _renderables.begin(); it != _renderables.end(); ++it) {
        SDLRenderable& renderable = it->second;
        if( !renderable.texture ) {
            continue;
        }
        if( renderable.isHidden ) {
            continue;
        }

        // SDL_QueryTexture(_texture, NULL, NULL, &texW, &texH);
        SDL_Rect rect = {
            renderable.posX + static_cast<int>(getCamera().getPos().x),
            renderable.posY + static_cast<int>(getCamera().getPos().y),
            renderable.width,
            renderable.height
        };
        SDL_RenderCopy(renderer, renderable.texture->getHandle(), NULL, &rect);

        // This is debug only
        /*
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        const int COUNT = 4;
        SDL_Point points[COUNT] = {
            {renderable.posX, renderable.posY},
            {renderable.posX + renderable.width, renderable.posY},
            {renderable.posX + renderable.width, renderable.posY + renderable.height},
            {renderable.posX, renderable.posY + renderable.height}
        };
        SDL_RenderDrawLines(renderer, points, COUNT);
        */
    }
    //Update the screen
    SDL_RenderPresent(renderer);

    //Take a quick break after all that hard work
    SDL_Delay(delta);
}


void SDLDevice::setIcon(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if( surface == nullptr ) {
        logger.error("Unable to load image: {}", path);
        return;
    }
    SDL_SetWindowIcon(window, surface);
}


Font::smrtptr SDLDevice::createFont(const char* fontName) {
    Font::smrtptr font = Font::smrtptr( new SDLFont(renderer, fontName));
    fontResources.push_back(font);
    logger.info("Font created {}", fontName);
    return font;
}

Texture::smrtptr SDLDevice::createTexture(const char* path) {
    auto screen = SDL_GetWindowSurface( window );
    //The final optimized image
    SDL_Surface* optimizedSurface = nullptr;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == nullptr ) {
        logger.error("Unable to load image");
        return Texture::smrtptr(nullptr);
    }

    //Convert surface to screen format
    SDL_SetColorKey(loadedSurface, SDL_RLEACCEL, loadedSurface->format->Amask);
    //SDL_SetSurfaceBlendMode(loadedSurface, SDL_BLENDMODE_BLEND);
    optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
    ///SDL_SetSurfaceBlendMode(optimizedSurface, SDL_BLENDMODE_BLEND);

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
    if( optimizedSurface == nullptr ) {
        logger.error("Unable to optimize the surface");
        return Texture::smrtptr(nullptr);
    }

    // Create the texture from the surface
    auto newTexture = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
    {
        Uint32 textureFormat;
        SDL_QueryTexture(newTexture, &textureFormat, NULL, NULL, NULL);
        printf("texture format: %s\n", SDL_GetPixelFormatName(textureFormat));
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(optimizedSurface);
    if( newTexture == nullptr ) {
        logger.error("Could not create texture from surface");
        return Texture::smrtptr(nullptr);
    }

    // It probably has alphas so just set the blendmode
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    logger.info("Texture created {}", path);
    return Texture::smrtptr(new SDLTexture(path, newTexture));
}


Renderable SDLDevice::createRenderableTexture(Texture::smrtptr tex, const Rect2d& rect) {
    SDLRenderable renderable = SDLRenderable(tex,
        static_cast<int>(rect.posX),
        static_cast<int>(rect.posY),
        static_cast<int>(rect.width),
        static_cast<int>(rect.height)
    );
    return createRenderable(renderable);
}

bool SDLDevice::updateRenderableTexture(Renderable texture, const Rect2d& rect, bool isHidden) {
    SDLRenderable& renderable = _renderables.at(texture);
    renderable.posX = static_cast<int>(rect.posX);
    renderable.posY = static_cast<int>(rect.posY);
    renderable.width = static_cast<int>(rect.width);
    renderable.height = static_cast<int>(rect.height);
    renderable.isHidden = isHidden;
    return true;
}
