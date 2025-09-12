#pragma once

#include "Frame.h"

class Animation 
{
public:
    Animation(const std::vector<Frame>& frames = {}, float fps = 0.0f, bool loop = true, bool reverse = false, SDL_RendererFlip orientation = SDL_FLIP_NONE);

    void addFrame(Frame frame);

    const SDL_Rect& getCurrentFrame() const;

    std::vector<Frame> frames;
    float fps;
    bool loop;
    bool reverse;
    SDL_RendererFlip orientation;
    size_t currentFrameIndex;
    float elapsedTime;
};
