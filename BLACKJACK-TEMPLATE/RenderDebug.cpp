#include "pch.h"
#include "RenderDebug.h"
#include "World.h"
#include "Renderer.h"

RenderDebug::RenderDebug()
{ }

void RenderDebug::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
    for (int32 i = 0; i < vertexCount; ++i) 
    {
        int32 j = (i + 1) % vertexCount;
        SDL_RenderDrawLine(Renderer::getSDLRenderer(), static_cast<int>(vertices[i].x * World::scale), static_cast<int>(vertices[i].y * World::scale), static_cast<int>(vertices[j].x * World::scale), static_cast<int>(vertices[j].y * World::scale));
    }
}

void RenderDebug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
    for (int32 i = 0; i < vertexCount; ++i) 
    {
        int32 j = (i + 1) % vertexCount;
        SDL_RenderDrawLine(Renderer::getSDLRenderer(), static_cast<int>(vertices[i].x * World::scale), static_cast<int>(vertices[i].y * World::scale), static_cast<int>(vertices[j].x * World::scale), static_cast<int>(vertices[j].y * World::scale));
    }
}

void RenderDebug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
}

void RenderDebug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
}

void RenderDebug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
    SDL_RenderDrawLine(Renderer::getSDLRenderer(), static_cast<int>(p1.x * World::scale), static_cast<int>(p1.y * World::scale), static_cast<int>(p2.x * World::scale), static_cast<int>(p2.y * World::scale));
}

void RenderDebug::DrawTransform(const b2Transform& xf) 
{
    const float k_axisScale = 0.4f;
    b2Vec2 p1 = xf.p, p2;

    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), 255, 0, 0, 255); // Red for x-axis
    SDL_RenderDrawLine(Renderer::getSDLRenderer(), static_cast<int>(p1.x * World::scale), static_cast<int>(p1.y * World::scale), static_cast<int>(p2.x * World::scale), static_cast<int>(p2.y * World::scale));

    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), 0, 255, 0, 255); // Green for y-axis
    SDL_RenderDrawLine(Renderer::getSDLRenderer(), static_cast<int>(p1.x * World::scale), static_cast<int>(p1.y * World::scale), static_cast<int>(p2.x * World::scale), static_cast<int>(p2.y * World::scale));
}

void RenderDebug::DrawPoint(const b2Vec2& p, float size, const b2Color& color) 
{
    SDL_SetRenderDrawColor(Renderer::getSDLRenderer(), static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
    SDL_Rect rect = { static_cast<int>((p.x - size / 2) * World::scale), static_cast<int>((p.y - size / 2) * World::scale), static_cast<int>(size * World::scale), static_cast<int>(size * World::scale) };
    SDL_RenderFillRect(Renderer::getSDLRenderer(), &rect);
}
