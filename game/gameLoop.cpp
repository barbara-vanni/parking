#include "gameLoop.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include<iostream>
#include "graphic_game/hpp_files/Button.hpp"
#include <SDL2/SDL.h>
#include <vector>


void mainLoop(Window& window, Grid& grid, std::vector<Button*>& buttons, Car& car) {
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
        int level = 0;  // Variable to store the level of the game
        SDL_GetMouseState(&x, &y);
        // cout << "Mouse is at position (" << x << ", " << y << ")" << endl;
        // cout<< "Entering event loop"<<endl;
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
                                if (buttons[0]->isClickedAtPosition(event.button.x, event.button.y)) {
                                    cout << "Button clicked!" << endl;
                                    window.switchState(State::Menu);
                                }

                        }
                    }
                    else if (window.getCurrentState() == State::Menu) {
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            if (buttons[2]->isClickedAtPosition(event.button.x, event.button.y)) {
                                cout << "Level 1 selected!" << endl;
                                level = 1;
                                buttons[2]->click();
                            } else if (buttons[3]->isClickedAtPosition(event.button.x, event.button.y)) {
                                cout << "Level 2 selected!" << endl;
                                level = 2;
                                buttons[3]->click();
                            } else if (buttons[4]->isClickedAtPosition(event.button.x, event.button.y)) {
                                cout << "Level 3 selected!" << endl;
                                level = 3;
                                buttons[4]->click();
                            }
                            if (buttons[1]->isClickedAtPosition(event.button.x, event.button.y)) {
                                cout << "Play button clicked!" << endl;
                                window.switchState(State::Parking);
                            }
                        }

                    }
                    break;

                case SDL_KEYDOWN:
                    cout << "Event type: " << event.type << endl;
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
                    }

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
                menuPage(window, buttons);
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



void introPage(Window& window, std::vector<Button*>& buttons){
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);
    window.drawText("Bienvenue dans le jeu !", 100, 100, 30);

    if (!buttons.empty()) {
        buttons[0]->draw();
    }

    SDL_RenderPresent(window.renderer);

}

void menuPage(Window& window, std::vector<Button*>& buttons){
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);
    window.drawText("Choose your Level", 600, 100, 30);

    if (!buttons.empty()) {
        buttons[2]->draw();
        buttons[3]->draw();
        buttons[4]->draw();
        if (buttons[2]->isClicked() || buttons[3]->isClicked() || buttons[4]->isClicked()){
            buttons[1]->draw();
        }
    }

    SDL_RenderPresent(window.renderer);
}

