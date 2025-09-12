#pragma once

class Renderer;
class DirectXRenderer;
class OpenGLRenderer;
class DefaultRenderer;
class Camera;

class RendererFactory
{
public:
    static Renderer* getInstance(std::string type, Camera* camera);
};