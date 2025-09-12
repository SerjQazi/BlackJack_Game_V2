#include "pch.h"
#include "Window.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "SceneManager.h"
#include "Camera.h"

Window::Window(std::string t, int x, int y, int w, int h, int worldWidth, int worldHeight, float zoom, Uint32 flags, std::string driver) : title(t), position(static_cast<float>(x), static_cast<float>(y)), width(w), height(h)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOG_ERROR("Could not initialize SDL...");
        SDL_Quit();
    }

    LOG_INFO("SDL initialized...");

    window = SDL_CreateWindow(title.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), width, height, flags);
    if (window == nullptr)
    {
        LOG_ERROR("Window could not be created...");
        SDL_Quit();
    }

    camera = new Camera(width, height, worldWidth, worldHeight, zoom);

    Renderer::getInstance()->rendererPIMPL = RendererFactory::getInstance(driver, camera);

    LOG_INFO("Window created...");
}

Window::Window(const GameConfiguration& config)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOG_ERROR("Could not initialize SDL...");
        SDL_Quit();
    }

    LOG_INFO("SDL initialized...");

    std::string title = config.windowTitle;
    position.x = config.x;
    position.y = config.y;
    width = config.SCREEN_WIDTH;
    height = config.SCREEN_HEIGHT;
    int worldWidth = config.worldWidth;
    int worldHeight = config.worldHeight;
    float zoom = config.zoom;
    std::string driver = config.renderer;
    Uint32 flags = SDL_WINDOW_SHOWN;
    if (config.fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (driver == "opengl")
    {
        flags |= SDL_WINDOW_OPENGL;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


    }

    window = SDL_CreateWindow(title.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), width, height, flags);
    if (window == nullptr)
    {
        LOG_ERROR("Error: Window could not be created...");
        SDL_Quit();
    }

    camera = new Camera(width, height, worldWidth, worldHeight, zoom);

    Renderer::getInstance()->rendererPIMPL = RendererFactory::getInstance(driver, camera);

    LOG_INFO("Window created...");
}

Window::~Window()
{
    LOG_INFO("Removing camera...");
    delete camera;
    SDL_DestroyWindow(window);

    LOG_INFO("Removing window...");
}

SDL_Window* Window::getSDLWindow()
{
    return window;
}

Camera* Window::getCamera()
{
    return camera;
}

Camera* Window::camera = nullptr;
SDL_Window* Window::window = nullptr;