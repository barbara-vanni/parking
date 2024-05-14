#include "../hpp_files/Window.hpp"
#include <iostream>

Window::Window(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        exit(1);
    }

    currentState = State::Intro; // Définir l'état initial comme "Intro"
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::isOpen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Window::switchState(State newState) {
    // Modification de la fenêtre en fonction du nouvel état
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
