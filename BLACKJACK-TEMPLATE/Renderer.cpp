#include "pch.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "Camera.h"

Renderer::Renderer() : camera(nullptr)
{ }

Renderer::~Renderer()
{
    LOG_INFO("Removing renderer...");

    SDL_DestroyRenderer(renderer);
    instance = nullptr;
}

Renderer* Renderer::getInstance()
{
    if (instance == nullptr)
        instance = new Renderer();
    return instance;
}

void Renderer::removeInstance()
{
    if (instance != nullptr)
    {
        delete rendererPIMPL;
    }
}

void Renderer::render()
{
    rendererPIMPL->render();
}

SDL_Renderer* Renderer::getSDLRenderer()
{
    return renderer;
}

Renderer* Renderer::rendererPIMPL = nullptr;
SDL_Renderer* Renderer::renderer = nullptr;
Renderer* Renderer::instance = nullptr;