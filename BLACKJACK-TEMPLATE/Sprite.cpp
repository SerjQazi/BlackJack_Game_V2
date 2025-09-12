#include "pch.h"
#include "Sprite.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "ConfigurationManager.h"

Sprite::Sprite(std::string goID, std::string f, float x, float y, int r, int c, int oX, int oY, bool v, double a, SDL_RendererFlip o) :
    filename(f), position{ x, y }, rows(r), cols(c), offsetX(oX), offsetY(oY), visible(v), angle(a), orientation(o), animating(false), currentAnimation(nullptr)
{ 
    id = goID;

    LOG_INFO("Creating sprite ", id, "...");

    texture = ResourceManager::getInstance()->addTexture(filename);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    width /= cols;
    height /= rows;
}

Sprite::Sprite(std::string goID, std::string f, float x, float y, bool v, double a, SDL_RendererFlip o)
    : position{ x, y }, rows(1), cols(1), offsetX(0), offsetY(0), visible(v), angle(a), orientation(o), animating(false), currentAnimation(nullptr)
{
    SpriteConfiguration* config = new SpriteConfiguration();
    ConfigurationManager::getInstance()->loadConfiguration(f, config);

    id = goID;

    LOG_INFO("Creating sprite ", id, " from file ", f, "...");

    filename = config->filename;
    width = config->frameWidth;
    height = config->frameHeight;
    texture = ResourceManager::getInstance()->addTexture(filename);

    for (auto item : config->animations)
    {
        Animation sequence = config->animations[item.first];
        int numFrames = static_cast<int>(sequence.frames.size());
        float duration = 1.0f / numFrames;
        sequence.fps = 1 / duration;
        addAnimation(item.first, sequence);
    }
}

Sprite::Sprite(const Sprite& other) :
    filename(other.filename), position(other.position), rows(other.rows), cols(other.cols), 
    offsetX(other.offsetX), offsetY(other.offsetY), visible(other.visible), angle(other.angle), orientation(other.orientation), animating(false), currentAnimation(nullptr)
{
    id = other.id + "-clone";

    LOG_INFO("Cloning sprite ", id, "...");

    texture = ResourceManager::getInstance()->addTexture(filename);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    width /= cols;
    height /= rows;
}

Sprite::~Sprite()
{
    LOG_INFO("Removing sprite ", id, "...");
}

Sprite* Sprite::clone()
{
    return new Sprite(*this);
}

void Sprite::update(float delta)
{
    if (animating)
    {
        //Elapsed Time Accumulation
        /*if (currentAnimation->frames.empty())
            return;

        currentAnimation->elapsedTime += delta;

        if (currentAnimation->elapsedTime >= (1000.0f / currentAnimation->fps) / 1000.0f)
        {
            currentAnimation->elapsedTime = 0.0f;
            currentAnimation->currentFrameIndex++;
            if (currentAnimation->currentFrameIndex >= currentAnimation->frames.size())
            {
                currentAnimation->currentFrameIndex = currentAnimation->loop ? 0 : currentAnimation->frames.size() - 1;
            }
        }*/

        //Frame Index Based on Time
        /*if (currentAnimation->frames.empty()) 
            return;

        currentAnimation->elapsedTime += delta;
        float totalDuration = 0.0;
        for (const Frame& frame : currentAnimation->frames) 
        {
            totalDuration += (1000.0f / currentAnimation->fps) / 1000.0f;
        }

        float timePerFrame = static_cast<float>(totalDuration) / currentAnimation->frames.size();
        currentAnimation->currentFrameIndex = static_cast<int>((currentAnimation->elapsedTime / timePerFrame)) % currentAnimation->frames.size();*/
        
        //LERP
        currentAnimation->elapsedTime += delta;
        float totalDuration = 0.0;
        for (const Frame& frame : currentAnimation->frames)
        {
            totalDuration += (1000.0f / currentAnimation->fps) / 1000.0f;
        }

        float progress = static_cast<float>(currentAnimation->elapsedTime) / totalDuration;
        int frameCount = static_cast<int>(currentAnimation->frames.size());
        currentAnimation->currentFrameIndex = static_cast<int>(progress * frameCount) % frameCount;
    }
}

void Sprite::render() 
{
    if (visible && currentAnimation) 
    {
        SDL_Rect source = currentAnimation->getCurrentFrame();

        if (camera) 
        {
            int screenX = static_cast<int>((position.x - camera->getViewPort().x) * camera->getZoom());
            int screenY = static_cast<int>((position.y - camera->getViewPort().y) * camera->getZoom());

            int transformedWidth = static_cast<int>(width * camera->getZoom());
            int transformedHeight = static_cast<int>(height * camera->getZoom());

            SDL_Rect dest = { screenX, screenY, transformedWidth, transformedHeight };
            SDL_RenderCopyEx(Renderer::getSDLRenderer(), texture, &source, &dest, angle, nullptr, orientation);
        }
        else 
        {
            SDL_Rect dest = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
            SDL_RenderCopyEx(Renderer::getSDLRenderer(), texture, &source, &dest, angle, nullptr, orientation);
        }
    }
}

void Sprite::addAnimation(const std::string& name, const Animation& animation)
{
    AnimationManager::getInstance()->addAnimation(name, animation);
}

void Sprite::addAnimation(const std::string& name, const int startIndex, const int length, int width, int height, int rows, int cols, float fps, bool loop, bool reverse, SDL_RendererFlip orientation)
{
    AnimationManager::getInstance()->addAnimation(name, startIndex, length, width, height, rows, cols, fps, loop, reverse, orientation);
}

void Sprite::removeAnimation(const std::string& name)
{
    AnimationManager::getInstance()->removeAnimation(name);
}

void Sprite::play(const std::string& name)
{
    LOG_INFO("Playing ", id, " animation ", name, "...");

    currentAnimation = AnimationManager::getInstance()->setCurrentAnimation(name);
    animating = true;
}

void Sprite::play(std::string name, float f, bool l, bool r, SDL_RendererFlip flip)
{
    LOG_INFO("Playing ", id, " animation ", name, "...");

    currentAnimation = AnimationManager::getInstance()->setCurrentAnimation(name);
    currentAnimation->fps = f;
    currentAnimation->loop = l;
    currentAnimation->reverse = r;
    currentAnimation->orientation = flip;
    animating = true;
}

void Sprite::stop()
{
    LOG_INFO("Stopping ", id, " animation...");

    animating = false;
}

void Sprite::setFPS(std::string goID, float fps)
{
    AnimationManager::getInstance()->setFPS(goID, fps);
}