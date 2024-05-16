#include "../hpp_files/Window.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>




Window::Window(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        exit(1);
    }

    currentState = State::Intro; 
}

Window::~Window() {
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::isOpen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                State newState;
                switch(currentState) {
                    case State::Intro:
                        newState = State::Menu;
                        break;
                    case State::Menu:
                        newState = State::Parking;
                        break;
                    default:
                        newState = State::Intro;
                        break;
                }
                switchState(newState);
            }
        }
    }
    return true;
}

bool Window::close() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Window::switchState(State newState) {
    switch(newState) {
        case State::Intro:
            SDL_SetWindowTitle(window, "Intro");
            break;
        case State::Menu: 
            SDL_SetWindowTitle(window, "Menu");
            break;
        case State::Parking: 
            SDL_SetWindowTitle(window, "Parking");
            break;
        default:
            std::cerr << "État invalide !" << std::endl;
            break;
    }
    currentState = newState;
}


State Window::getCurrentState() {
    return currentState;
}

void Window::drawText(const std::string &text, int x, int y, int size){

    TTF_Font* font = TTF_OpenFont("font/Oswald.ttf", 24);

    if (font == nullptr) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255}; 

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == nullptr) {
        std::cerr << "Erreur lors de la création de la surface de texte : " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }


    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (textTexture == nullptr) {
        std::cerr << "Erreur lors de la création de la texture de texte : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);


    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

}



