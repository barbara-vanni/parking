#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/Grid.hpp"
#include <iostream>
#include <cstdlib>


int main(int argc, char *argv[]) {
    Window window("Intro", 1500, 720);

    // Creation of the grid object and display it on terminal
    Grid grid(6, 6, 3, 0, 3);
    grid.Display();

    std::cout << "la fenetre est ouverte" << std::endl;
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
                                nextState = State::Intro; 
                                break;
                        }
                        window.switchState(nextState);
                    }
                    break;
                default:
                    break;
            }
            if (window.getCurrentState() == State::Intro) {
                window.drawText("Bienvenue dans le jeu !", 100, 100, 30);
            } else if (window.getCurrentState() == State::Menu) {
                window.drawText("Menu", 100, 100, 30);
            } else if (window.getCurrentState() == State::Parking) {
                window.drawText("Parking", 100, 100, 30);
            }
        
        }


    }
    std::cout << "la fenetre est fermée" << std::endl;

    return EXIT_SUCCESS;
}
