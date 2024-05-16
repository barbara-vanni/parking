#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <string>

class Button {
private:
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Color color;
    std::string text;
    int size;
public:
    Button(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string &text, int size);
    ~Button();
    void draw();
    bool isClicked(int x, int y);
};

#endif