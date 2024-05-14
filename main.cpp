// #include "game/graphic_game/hpp_files/Window.hpp"
// #include <iostream>                     
// #include <cstdlib>
// #include <iostream>

// int main(int argc, char *argv[]) {
//     Window window("Intro", 1500, 720);

//     while (window.isOpen()) {
//         SDL_Event event;
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     window.switchState(State::Parking); // Spécifier l'état Parking lors de la fermeture de la fenêtre
//                     break;
//                 case SDL_KEYDOWN:
//                     if (event.key.keysym.sym == SDLK_RETURN) {
//                         State currentState = window.getCurrentState();
//                         State nextState;
//                         // Déterminer l'état suivant en fonction de l'état actuel
//                         switch(currentState) {
//                             case State::Intro:
//                                 nextState = State::Menu;
//                                 break;
//                             case State::Menu:
//                                 nextState = State::Parking;
//                                 break;
//                             case State::Parking:
//                                 nextState = State::Intro;
//                                 break;
//                             default:
//                                 nextState = State::Intro; // État par défaut
//                                 break;
//                         }
//                         window.switchState(nextState); // Passer à l'état suivant
//                     }
//                     break;
//                 default:
//                     break;
//             }
//         }

//         // Afficher l'état actuel
//         std::cout << "État actuel : ";
//         switch(window.getCurrentState()) {
//             case State::Intro:
//                 std::cout << "Intro" << std::endl;
//                 break;
//             case State::Menu:
//                 std::cout << "Menu" << std::endl;
//                 break;
//             case State::Parking:
//                 std::cout << "Parking" << std::endl;
//                 break;
//             default:
//                 std::cout << "Inconnu" << std::endl;
//                 break;
//         }

//     }

//     return EXIT_SUCCESS;
// }
#include "game/graphic_game/hpp_files/Window.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    Window window("Intro", 1500, 720);
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
                                nextState = State::Intro; // État par défaut
                                break;
                        }
                        window.switchState(nextState); // Changer d'état
                    }
                    break;
                default:
                    break;
            }
        }

        // std::cout << "État actuel : ";
        // switch(window.getCurrentState()) {
        //     case State::Intro:
        //         std::cout << "Intro" << std::endl;
        //         break;
        //     case State::Menu:
        //         std::cout << "Menu" << std::endl;
        //         break;
        //     case State::Parking:
        //         std::cout << "Parking" << std::endl;
        //         break;
        //     default:
        //         std::cout << "Inconnu" << std::endl;
        //         break;
        // }
    }
    std::cout << "la fenetre est fermée" << std::endl;

    return EXIT_SUCCESS;
}
