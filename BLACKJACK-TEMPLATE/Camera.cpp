#include "pch.h"
#include "Camera.h"
#include "Renderer.h"

Camera::Camera(int screenWidth, int screenHeight, int worldWidth, int worldHeight, float zoom)
    : targetPosition(nullptr), targetWidth(0), targetHeight(0), screenWidth(screenWidth), screenHeight(screenHeight), 
    worldWidth(worldWidth), worldHeight(worldHeight), zoom(zoom), active(false)
{
    LOG_INFO("Creating camera...");
    viewPort = { 0, 0, screenWidth, screenHeight };
    SDL_RenderSetViewport(Renderer::getSDLRenderer(), &viewPort);
    updateViewport();
}

void Camera::setPosition(int x, int y)
{
    viewPort.x = x;
    viewPort.y = y;
    clampToWorldBounds();
}

void Camera::move(int dx, int dy)
{
    viewPort.x += dx;
    viewPort.y += dy;
    clampToWorldBounds();
}

void Camera::follow(glm::vec2* targetPosition, int targetWidth, int targetHeight)
{
    if (!targetPosition)
    {
        LOG_ERROR("Error: Camera cannot follow a null target...");
        return;
    }

    this->targetPosition = targetPosition;
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;
}

void Camera::update(float delta)
{
    if (targetPosition)
    {
        viewPort.x = static_cast<int>(targetPosition->x + targetWidth / 2 - viewPort.w / 2);
        viewPort.y = static_cast<int>(targetPosition->y + targetHeight / 2 - viewPort.h / 2);
        clampToWorldBounds();
    }
}

void Camera::setZoom(float zoomLevel)
{
    zoom = zoomLevel;
    if (zoom < 0.1f)
        zoom = 0.1f;
    updateViewport();
}

void Camera::adjustZoom(float deltaZoom)
{
    zoom += deltaZoom;
    if (zoom < 0.1f)
        zoom = 0.1f;
    updateViewport();
}

void Camera::updateViewport()
{
    viewPort.w = static_cast<int>(screenWidth / zoom);
    viewPort.h = static_cast<int>(screenHeight / zoom);
    clampToWorldBounds();
}

SDL_Rect Camera::getViewPort() const
{
    return viewPort;
}

float Camera::getZoom() const
{
    return zoom;
}

void Camera::clampToWorldBounds()
{
    if (viewPort.x < 0)
        viewPort.x = 0;

    if (viewPort.y < 0)
        viewPort.y = 0;

    if (viewPort.x > worldWidth - viewPort.w)
        viewPort.x = worldWidth - viewPort.w;
    
    if (viewPort.y > worldHeight - viewPort.h)
        viewPort.y = worldHeight - viewPort.h;
}