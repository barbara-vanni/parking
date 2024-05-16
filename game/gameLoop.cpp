#include "gameLoop.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include<iostream>
#include "graphic_game/hpp_files/Button.hpp"
#include <SDL2/SDL.h>
#include <vector>


void mainLoop(Window& window, Grid& grid, std::vector<Button>& buttons, Car& car) {
    std::cout << "Game loop started!" << std::endl;

    bool gridChanged = true; // Variable to check if the grid has changed
    bool stateChanged = true; // Variable to check if the state has changed 

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    bool gameisrunning = true;   

    while (gameisrunning) {
        frameStart = SDL_GetTicks();

        int x, y;
        SDL_GetMouseState(&x, &y);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    cout << "Event type: " << event.type << endl;
                    gameisrunning = false;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    cout << "Event type: " << event.type << endl;
                    if (window.getCurrentState() == State::Intro) {
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            for (Button& buttonBegin : buttons) {
                                if (buttonBegin.isClicked(event.button.x, event.button.y)) {
                                    cout << "Button clicked!" << endl;
                                    window.switchState(State::Menu);
                                }
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (window.getCurrentState() == State::Parking) {
                        // Déplacement de la voiture lorsque les touches directionnelles sont enfoncées
                        switch (event.key.keysym.sym) {
                            case SDLK_UP:
                                car.moveUp();
                                gridChanged = true;
                                break;
                            case SDLK_DOWN:
                                car.moveDown();
                                gridChanged = true;
                                break;
                            case SDLK_LEFT:
                                car.moveLeft();
                                gridChanged = true;
                                break;
                            case SDLK_RIGHT:
                                car.moveRight();
                                gridChanged = true;
                                break;
                            default:
                                break;
                        }
                    } else {
                        // Changement d'état si la touche "Return" est enfoncée
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            State newState;
                            switch(window.getCurrentState()) {
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
                            window.switchState(newState);
                            stateChanged = true; // Indique que l'état a changé
                        }
                    }
                    break;
                default:
                    break;
            }   
        }
    
        // Render game state outside of the SDL_PollEvent loop
        switch (window.getCurrentState()) {
            case State::Intro:
                introPage(window, buttons);
                break;
            case State::Menu:
                SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
                SDL_RenderClear(window.renderer);
                window.drawText("Menu", 100, 100, 30);
                SDL_RenderPresent(window.renderer);
                break;
            case State::Parking:
                if (stateChanged) {
                    SDL_RenderClear(window.renderer); 
                    grid.setCar(car);
            grid.DisplayOnScreen(window.window, window.renderer); 
                    // stateChanged = false;
                }
                break;
            default:
                std::cerr << "État invalide !" << std::endl;
                break;
        }
        
        SDL_RenderPresent(window.renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    std::cout << "la fenetre est fermée" << std::endl;
    std::cout << "Game loop ended!" << std::endl;
}


void introPage(Window& window, std::vector<Button>& buttons){
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);
    window.drawText("Bienvenue dans le jeu !", 100, 100, 30);

    for (Button& button : buttons) {
        button.draw();
    }
    SDL_RenderPresent(window.renderer);

}