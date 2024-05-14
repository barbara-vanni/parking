// #include "../hpp_files/Window.hpp"
// #include <iostream>

// Window::Window(const char* title, int width, int height) {
//     SDL_Init(SDL_INIT_EVERYTHING);

//     window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

//     if (window == nullptr) {
//         std::cout << "Erreur : " << SDL_GetError() << std::endl;
//         exit(1);
//     }
// }

// Window::~Window() {
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }

// bool Window::isOpen() {
//     SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) {
//             return false;
//         }
//     }
//     return true;
// }
#include "../hpp_files/Window.hpp"
#include <iostream>

Window::Window(const char* introTitle, const char* menuTitle, const char* parkingTitle, int width, int height) {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Création de la fenêtre intro
    introWindow = SDL_CreateWindow(introTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (introWindow == nullptr) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Création de la fenêtre menu
    menuWindow = SDL_CreateWindow(menuTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (menuWindow == nullptr) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Création de la fenêtre parking
    parkingWindow = SDL_CreateWindow(parkingTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (parkingWindow == nullptr) {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        exit(1);
    }

    currentWindowState = 0; // Initialisation à l'état Intro
}

Window::~Window() {
    // Destruction des fenêtres
    SDL_DestroyWindow(introWindow);
    SDL_DestroyWindow(menuWindow);
    SDL_DestroyWindow(parkingWindow);

    // Quitter SDL
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

void Window::switchState(int newState) {
    switch(newState) {
        case 0: // Intro
            SDL_ShowWindow(introWindow);
            SDL_HideWindow(menuWindow);
            SDL_HideWindow(parkingWindow);
            break;
        case 1: // Menu
            SDL_HideWindow(introWindow);
            SDL_ShowWindow(menuWindow);
            SDL_HideWindow(parkingWindow);
            break;
        case 2: // Parking
            SDL_HideWindow(introWindow);
            SDL_HideWindow(menuWindow);
            SDL_ShowWindow(parkingWindow);
            break;
        default:
            std::cerr << "Invalid state!" << std::endl;
            break;
    }
    currentWindowState = newState;
}

int Window::getCurrentState() {
    return currentWindowState;
}
