#include "game/graphic_game/hpp_files/Window.hpp"
#include <iostream>                     
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    // Création de l'objet Window avec les titres des fenêtres
    Window window("Intro", "Menu", "Parking", 1500, 720);

    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    window.switchState(-1); // Quitter l'application si la fenêtre est fermée
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) { // Si la touche Entrée est enfoncée
                        int currentState = window.getCurrentState();
                        int nextState = (currentState + 1) % 3; // Passer à l'état suivant (Intro -> Menu -> Parking -> Intro)
                        window.switchState(nextState);
                    }
                    break;
                default:
                    break;
            }
        }

        // Gestion des différents états
        int currentState = window.getCurrentState();

        // Affichage de l'état actuel pour débogage
        std::cout << "État actuel : ";
        switch(currentState) {
            case 0:
                std::cout << "Intro" << std::endl;
                break;
            case 1:
                std::cout << "Menu" << std::endl;
                break;
            case 2:
                std::cout << "Parking" << std::endl;
                break;
            default:
                std::cout << "Inconnu" << std::endl;
                break;
        }

        // Mettre à jour les états en fonction des événements ou de la logique du jeu
    }

    return EXIT_SUCCESS;
}



