#pragma once

#include "Animation.h"
#include "Frame.h"

class Renderer;

class AnimationManager 
{
public:
    ~AnimationManager();

    static AnimationManager* getInstance();
    static void removeInstance();

    const Animation& findAnimation(const std::string& name) const;
    void addAnimation(const std::string& name, const Animation& animation);
    void addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps = 0.0f, bool loop = true, bool reverse = false, SDL_RendererFlip orientation = SDL_FLIP_NONE);
    void removeAnimation(const std::string& name);
    Animation* setCurrentAnimation(const std::string& name);

    void setFPS(std::string goID, float fps);

private:
    AnimationManager();
    
    std::map<std::string, Animation> animations;
    Animation* currentAnimation;

    static AnimationManager* instance;
};
