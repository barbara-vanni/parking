#include "gameLoop.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include<iostream>
#include <SDL2/SDL.h>

void mainLoop(Window& window, Grid& grid, Car& car) {
    std::cout << "Game loop started!" << std::endl;

    bool gridChanged = true; // Variable to check if the grid has changed

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (window.isOpen()) {
        frameStart = SDL_GetTicks();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    window.close();
                    break;

                // case SDL_KEYDOWN:
                //     if (window.getCurrentState() == State::Parking) {
                //         if (event.key.keysym.sym == SDLK_RIGHT) {
                //             cout << "right" << endl;
                //             // grid.Move(1);
                //             gridChanged = true;
                //         } else if (event.key.keysym.sym == SDLK_LEFT) {
                //             cout << "left" << endl;
                //             // grid.Move(-1);
                //             gridChanged = true;
                case SDL_KEYDOWN:
                        if (window.getCurrentState() == State::Parking) {
                            if (event.key.keysym.sym == SDLK_UP) {
                                car.moveUp();    
                                gridChanged = true;
                            } else if (event.key.keysym.sym == SDLK_DOWN) {
                                car.moveDown(); 
                                gridChanged = true;
                            } else if (event.key.keysym.sym == SDLK_LEFT) {
                                car.moveLeft();  
                                gridChanged = true;
                            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                                car.moveRight(); 
                                gridChanged = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        

        // Render game state outside of the SDL_PollEvent loop
        if (window.getCurrentState() == State::Intro) {
            window.drawText("Bienvenue dans le jeu !", 100, 100, 30);
            const char* error = SDL_GetError();
            if (*error) {
                std::cout << "SDL Error: " << error << std::endl;
                SDL_ClearError();
            }
            SDL_RenderClear(window.renderer);
            SDL_RenderPresent(window.renderer);
        } 

        if (window.getCurrentState() == State::Parking && gridChanged) {
            grid.setCar(car);
            grid.DisplayOnScreen(window.window, window.renderer);
            SDL_RenderPresent(window.renderer);
            gridChanged = false;
        }

        SDL_RenderClear(window.renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    std::cout << "la fenetre est fermée" << std::endl;
    std::cout << "Game loop ended!" << std::endl;
}