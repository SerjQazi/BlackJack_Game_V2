#include "pch.h"
#include "RendererFactory.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "DefaultRenderer.h"
#include "Camera.h"

Renderer* RendererFactory::getInstance(std::string type, Camera* camera)
{
    int driver = -1;
    int numRenderDrivers = SDL_GetNumRenderDrivers();
    if (numRenderDrivers < 1)
    {
        LOG_INFO("No render drivers available...");
        SDL_Quit();
    }

    LOG_INFO("Available render drivers: ", numRenderDrivers);

    for (int i = 0; i < numRenderDrivers; ++i)
    {
        SDL_RendererInfo info;
        if (SDL_GetRenderDriverInfo(i, &info) != 0)
        {
            LOG_INFO("Could not find drive info...");
            continue;
        }

        LOG_INFO("Render Driver ", i, ": ", info.name);
        LOG_INFO("\tFlags: ", info.flags);
        LOG_INFO("\tNum Texture Formats: ", info.num_texture_formats);
        for (Uint32 j = 0; j < info.num_texture_formats; ++j)
            LOG_INFO("\tTexture Format ", j, ": ", SDL_GetPixelFormatName(info.texture_formats[j]));
        LOG_INFO("\tMax Texture Width: ", info.max_texture_width);
        LOG_INFO("\tMax Texture Height: ", info.max_texture_height);
    
        if (std::string(info.name) == type && (type == "direct3d" || type == "opengl"))
            driver = i;
    }

    LOG_INFO("Creating renderer ", type);

    if (type == "direct3d" || type == "direct3d11" || type == "direct3d12")
    {
        return new DirectXRenderer(driver, camera);
    }
    else if (type == "opengl")
    {
        return new OpenGLRenderer(driver, camera);
    }
    else
    {
        return new DefaultRenderer(driver, camera);
    }

    return nullptr;
}