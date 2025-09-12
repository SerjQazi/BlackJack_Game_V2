#include "pch.h"
#include "OpenGLQuad.h"

OpenGLQuad::OpenGLQuad(float x, float y, float frameWidth, float frameHeight, float width, float height)
{
    float u = 0;
    float v = 0;

    float ndcX = 2.0f * x / GameConfiguration::SCREEN_WIDTH - 1.0f;
    float ndcY = 1.0f - 2.0f * y / GameConfiguration::SCREEN_HEIGHT;
    float ndcWidth = 2.0f * frameWidth / GameConfiguration::SCREEN_WIDTH;
    float ndcHeight = 2.0f * frameHeight / GameConfiguration::SCREEN_HEIGHT;

    vertices = {
        { glm::vec3(ndcX, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, v / height) },
        { glm::vec3(ndcX, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, v / height) }
    };
}

OpenGLQuad::OpenGLQuad(float x, float y, float frameWidth, float frameHeight, float width, float height, int currentFrame)
{
    float u = (currentFrame % (static_cast<int>(width / frameWidth))) * frameWidth;
    float v = (currentFrame / (static_cast<int>(width / frameWidth))) * frameHeight;

    float ndcX = 2.0f * x / GameConfiguration::SCREEN_WIDTH - 1.0f;
    float ndcY = 1.0f - 2.0f * y / GameConfiguration::SCREEN_HEIGHT;
    float ndcWidth = 2.0f * frameWidth / GameConfiguration::SCREEN_WIDTH;
    float ndcHeight = 2.0f * frameHeight / GameConfiguration::SCREEN_HEIGHT;

    vertices = {
        { glm::vec3(ndcX, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, v / height) },
        { glm::vec3(ndcX, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, v / height) }
    };
}

OpenGLQuad::~OpenGLQuad()
{
	vertices.clear();
}

void OpenGLQuad::transform(float x, float y, float frameWidth, float frameHeight, float width, float height, int currentFrame)
{
    float u = (currentFrame % (static_cast<int>(width / frameWidth))) * frameWidth;
    float v = (currentFrame / (static_cast<int>(width / frameWidth))) * frameHeight;

    float ndcX = 2.0f * x / GameConfiguration::SCREEN_WIDTH - 1.0f;
    float ndcY = 1.0f - 2.0f * y / GameConfiguration::SCREEN_HEIGHT;
    float ndcWidth = 2.0f * frameWidth / GameConfiguration::SCREEN_WIDTH;
    float ndcHeight = 2.0f * frameHeight / GameConfiguration::SCREEN_HEIGHT;

    vertices.clear();

    vertices = {
        { glm::vec3(ndcX, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, (v + frameHeight) / height) },
        { glm::vec3(ndcX + ndcWidth, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2((u + frameWidth) / width, v / height) },
        { glm::vec3(ndcX, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(u / width, v / height) }
    };
}

void OpenGLQuad::transform(float x, float y, float width, float height, SDL_Rect frame, bool flip)
{
    float uLeft;
    float uRight;
    float vTop = frame.y / height;
    float vBottom = (frame.y + frame.h) / height;

    if (flip)
    {
        uLeft = (frame.x + frame.w) / width; 
        uRight = frame.x / width;
    }
    else
    {
        uLeft = frame.x / width;
        uRight = (frame.x + frame.w) / width;
    }

    float ndcX = 2.0f * x / GameConfiguration::SCREEN_WIDTH - 1.0f;
    float ndcY = 1.0f - 2.0f * y / GameConfiguration::SCREEN_HEIGHT;
    float ndcWidth = 2.0f * frame.w / GameConfiguration::SCREEN_WIDTH;
    float ndcHeight = 2.0f * frame.h / GameConfiguration::SCREEN_HEIGHT;

    vertices.clear();

    vertices = {
        { glm::vec3(ndcX, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(uLeft, vBottom) },
        { glm::vec3(ndcX + ndcWidth, ndcY - ndcHeight, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(uRight, vBottom) },
        { glm::vec3(ndcX + ndcWidth, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(uRight, vTop) },
        { glm::vec3(ndcX, ndcY, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(uLeft, vTop) }
    };
}

std::vector<OpenGLVertex> OpenGLQuad::getVertices() const
{
    return vertices;
}