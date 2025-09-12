#pragma once

class Renderer;

class Camera
{
public:
    Camera(int screenWidth = 0, int screenHeight = 0, int worldWidth = 0, int worldHeight = 0, float zoom = 1.0f);

    void update(float delta);
    
    void setPosition(int x, int y);
    
    void move(int dx, int dy);
    void follow(glm::vec2* targetPosition, int targetWidth, int targetHeight);
    
    void setZoom(float zoomLevel);
    void adjustZoom(float deltaZoom);

    SDL_Rect getViewPort() const;
    float getZoom() const;

private:
    SDL_Rect viewPort;
    glm::vec2* targetPosition;
    int targetWidth;
    int targetHeight;
    int screenWidth;
    int screenHeight;
    int worldWidth;
    int worldHeight;
    float zoom;
    bool active;

    void clampToWorldBounds();
    void updateViewport();
};
