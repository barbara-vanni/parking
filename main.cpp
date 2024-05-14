
#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/Grid.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>

int main(int argc, char *argv[]) {
    TTF_Init(); // Initialisation de la bibliothèque SDL_ttf
    Window window("Intro", 1500, 720);

    // Creation of the grid object and display it on terminal
    Grid grid(6, 6, 3, 0, 3, 2);
    grid.Display();

    std::cout << "la fenetre est ouverte" << std::endl;

    bool gridChanged = true; // Variable to check if the grid has changed

    while (window.isOpen()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Vérifier si la fermeture est due à l'utilisateur ou à un changement d'état
                    if (window.getCurrentState() != State::Parking) {
                        State currentState = window.getCurrentState();
                        State nextState;
                        // Logique de transition d'état
                        switch(currentState) {
                            case State::Intro:
                                nextState = State::Menu;
                                break;
                            case State::Menu:
                                nextState = State::Parking;
                                break;
                            case State::Parking:
                                nextState = State::Intro;
                                break;
                            default:
                                nextState = State::Intro; // État par défaut
                                break;
                        }
                        window.switchState(nextState); // Changer d'état
                    }
                    break;
                case SDL_KEYDOWN:
                    cout << "Key pressed: " << event.key.keysym.sym << endl;
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        State currentState = window.getCurrentState();
                        State nextState;
                        // Logique de transition d'état
                        switch(currentState) {
                            case State::Intro:
                                nextState = State::Menu;
                                break;
                            case State::Menu:
                                nextState = State::Parking;
                                break;
                            case State::Parking:
                                nextState = State::Intro;
                                break;
                            default:
                                nextState = State::Intro; // État par défaut
                                break;
                        }
                        window.switchState(nextState); // Changer d'état
                    }
                    if (window.getCurrentState() == State::Parking) {
                        if (event.key.keysym.sym == SDLK_RIGHT) {
                            cout << "right" << endl;
                            grid.Move(1);
                            gridChanged = true;
                        } else if (event.key.keysym.sym == SDLK_LEFT) {
                            cout << "left" << endl;
                            grid.Move(-1);
                            gridChanged = true;
                        }
                    }
                    break;
                    default:
                        break;
            }

        if (window.getCurrentState() == State::Intro) {
            SDL_RenderClear(window.renderer);
            window.drawText("Bienvenue dans le jeu !", 100, 100, 30);
            const char* error = SDL_GetError();
            if (*error) {
                std::cout << "SDL Error: " << error << std::endl;
                SDL_ClearError();
                }
            SDL_RenderPresent(window.renderer);
        } 

        }


        if (window.getCurrentState() == State::Parking && gridChanged) {
            // std::cout << "Displaying grid..." << std::endl;
            SDL_RenderClear(window.renderer);
            grid.DisplayOnScreen(window.window, window.renderer);
            gridChanged = false;
            SDL_RenderPresent(window.renderer);
        }

    }
    std::cout << "la fenetre est fermée" << std::endl;

    TTF_Quit(); // Fermeture de la bibliothèque SDL_ttf
    return EXIT_SUCCESS;
}
