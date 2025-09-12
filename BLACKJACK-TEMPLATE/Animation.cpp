#include "pch.h"
#include "Animation.h"

Animation::Animation(const std::vector<Frame>& frames, float fps, bool loop, bool reverse, SDL_RendererFlip orientation)
    : frames(frames), fps(fps), loop(loop), reverse(reverse), orientation(orientation), currentFrameIndex(0), elapsedTime(0)
{ }

void Animation::addFrame(Frame frame)
{
    frames.push_back(frame);
}

const SDL_Rect& Animation::getCurrentFrame() const 
{
    return frames[currentFrameIndex].source;
}