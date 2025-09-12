#pragma once

class ResourceManager;

class Font
{
public:
    Font(std::string filename, int size = 1, SDL_Color color = { 0, 0, 0, 255 });
    ~Font();

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    std::string getFilename() const;
    int getSize() const;
    SDL_Color getColor() const;
    TTF_Font* getSDLFont() const;

private:
    TTF_Font* font;
    std::string filename;
    SDL_Color color;
    int size;
};