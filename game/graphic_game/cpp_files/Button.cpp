#include "../hpp_files/Button.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;


Button::Button(SDL_Renderer *renderer, int x, int y, int w, int h, const std::string &text, int size) {
    this->renderer = renderer;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    this->text = text;
    this->size = size;

    TTF_Font *font = TTF_OpenFont("font/Oswald.ttf", size);
    if (font == nullptr) {
        std::cout << "Erreur lors de l'ouverture de la police : " << TTF_GetError() << std::endl;
        exit(1);
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    if (surface == nullptr) {
        std::cout << "Erreur lors de la création de la surface : " << TTF_GetError() << std::endl;
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cout << "Erreur lors de la création de la texture : " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::draw() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Button::isClicked(int x, int y) {
    // Debug output to check coordinates
    cout << "Button rect: x=" << rect.x << ", y=" << rect.y << ", w=" << rect.w << ", h=" << rect.h << endl;
    cout << "Mouse click: x=" << x << ", y=" << y << endl;

    // Check if the click is within the button's rectangle
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}
