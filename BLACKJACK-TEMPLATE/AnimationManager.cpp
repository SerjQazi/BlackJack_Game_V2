#include "pch.h"
#include "AnimationManager.h"
#include "Renderer.h"

AnimationManager::AnimationManager() : currentAnimation(nullptr)
{
    LOG_INFO("Initializing animation manager...");
}

AnimationManager::~AnimationManager()
{
    animations.clear();
}

AnimationManager* AnimationManager::getInstance()
{
    if (instance == nullptr)
        instance = new AnimationManager();
    return instance;
}

void AnimationManager::removeInstance()
{
    if (instance)
        delete instance;
}

const Animation& AnimationManager::findAnimation(const std::string& name) const
{
    return animations.at(name);
}

void AnimationManager::addAnimation(const std::string& name, const Animation& animation)
{
    auto it = animations.find(name);
    if (it == animations.end())
    {
        animations[name] = animation;

        LOG_INFO("Creating animation ", name, "...");
    }
}

void AnimationManager::addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps, bool loop, bool reverse, SDL_RendererFlip orientation)
{
    std::vector<Frame> frames;
    auto it = animations.find(name);

    if (it == animations.end())
    {
        for (int i = 0; i < length; ++i)
        {
            int index = startIndex + i;
            int x = (index % cols) * width;
            int y = (index / cols) * height;

            Frame frame(std::to_string(i), { x, y, width, height });
            frames.push_back(frame);
        }

        Animation animation(frames, fps, loop, reverse, orientation);
        animations[name] = animation;

        LOG_INFO("Creating animation ", name, "...");
    }
}

void AnimationManager::removeAnimation(const std::string& name)
{
    animations.erase(name);
}

Animation* AnimationManager::setCurrentAnimation(const std::string& name)
{
    auto it = animations.find(name);
    if (it != animations.end())
        currentAnimation = &it->second;
    return currentAnimation;
}

void AnimationManager::setFPS(std::string goID, float fps)
{
    animations.at(goID).fps = fps;
}

AnimationManager* AnimationManager::instance = nullptr;