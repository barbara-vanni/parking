#include "gameLoop.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include "logic_game/hpp_files/StockCar.hpp"
#include "graphic_game/hpp_files/Button.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void mainLoop(Window& window, Grid& grid, std::vector<Button>& buttons, StockCar& stockCar, int& selectedCarIndex) {
    std::cout << "Game loop started!" << std::endl;

    bool gridChanged = true;
    bool stateChanged = true;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    bool gameisrunning = true;
    bool victory = false;

    std::vector<SDL_Texture*> gifFrames = window.loadGifFrames("assets/images", 52);  // 10 frames par exemple
    int currentFrame = 0;
    Uint32 lastGifFrameTime = 0;
    const Uint32 gifFrameDelay = 60;  // Délai de 100 ms entre chaque frame

    while (gameisrunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "Event type: " << event.type << std::endl;
                    gameisrunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    std::cout << "Event type: " << event.type << std::endl;
                    if (window.getCurrentState() == State::Intro) {
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            for (Button& buttonBegin : buttons) {
                                if (buttonBegin.isClicked(event.button.x, event.button.y)) {
                                    std::cout << "Button clicked!" << std::endl;
                                    window.switchState(State::Menu);
                                    stateChanged = true;
                                }
                            }
                        }
                    } else if (event.button.button == SDL_BUTTON_LEFT && window.getCurrentState() == State::Parking) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        for (int i = 0; i < stockCar.getStockCar().size(); ++i) {
                            Car& car = stockCar.getStockCar()[i];
                            int carX = car.getPosX() * 110;
                            int carY = car.getPosY() * 110;
                            int carW = car.isHorizontalOrientation() ? car.getWidth() * 100 : car.getHeight() * 100;
                            int carH = car.isHorizontalOrientation() ? car.getHeight() * 100 : car.getWidth() * 100;

                            if (x >= carX && x <= carX + carW && y >= carY && y <= carY + carH) {
                                selectedCarIndex = i;
                                grid.setSelectedCar(&car);
                                std::cout << "Car selected: " << i << std::endl;
                                break;
                            }
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    std::cout << "Key event (down): " << event.key.keysym.sym << std::endl;
                    if (window.getCurrentState() == State::Parking && selectedCarIndex != -1) {
                        Car& selectedCar = stockCar.getStockCar()[selectedCarIndex];
                        switch (event.key.keysym.sym) {
                            case SDLK_UP:
                                std::cout << "Key UP pressed" << std::endl;
                                selectedCar.moveUp();
                                break;
                            case SDLK_DOWN:
                                std::cout << "Key DOWN pressed" << std::endl;
                                selectedCar.moveDown();
                                break;
                            case SDLK_LEFT:
                                std::cout << "Key LEFT pressed" << std::endl;
                                selectedCar.moveLeft();
                                break;
                            case SDLK_RIGHT:
                                std::cout << "Key RIGHT pressed" << std::endl;
                                selectedCar.moveRight();
                                break;
                            default:
                                std::cout << "Unhandled key press: " << event.key.keysym.sym << std::endl;
                                break;
                        }

                        // Vérifier si la voiture du joueur est à la sortie
                        std::cout << "Car position: (" << selectedCar.getPosX() << ", " << selectedCar.getPosY() << ")" << std::endl;
                        std::cout << "Exit position: (" << grid.getExitRow() << ", " << grid.getExitCol() << ")" << std::endl;

                        if (selectedCar.getIsPlayer() && selectedCar.getPosX() == grid.getExitCol() - 1 && selectedCar.getPosY() == grid.getExitRow()) {
                            victory = true;
                        }


                        gridChanged = true;
                    } else {
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            std::cout << "Return key pressed" << std::endl;
                            State newState;
                            switch (window.getCurrentState()) {
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
                            stateChanged = true;
                        }
                    }
                    break;
            }
        }

        // Render game state outside of the SDL_PollEvent loop
        switch (window.getCurrentState()) {
            case State::Intro:
                // Mettez à jour la frame du GIF si le délai est écoulé et que nous ne sommes pas à la dernière frame
                if (SDL_GetTicks() - lastGifFrameTime > gifFrameDelay && currentFrame < gifFrames.size() - 1) {
                    currentFrame++;
                    lastGifFrameTime = SDL_GetTicks();
                }
                introPage(window, buttons, gifFrames, currentFrame);
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
                    grid.setStockCar(stockCar.getStockCar());
                    grid.DisplayOnScreen(window.window, window.renderer);
                    stateChanged = false;
                }
                if (gridChanged) {
                    SDL_RenderClear(window.renderer);
                    grid.setStockCar(stockCar.getStockCar());
                    grid.DisplayOnScreen(window.window, window.renderer);
                    gridChanged = false;
                }
                if (victory) {
                    window.drawText("Victoire!", 900, 50, 100); 
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

        if (victory) {
            SDL_Delay(3000); 

            std::cout << "Resetting car positions..." << std::endl; 
            stockCar.resetCars(); 

            window.switchState(State::Menu); 
            victory = false; 
            stateChanged = true; 
        }
    }

    std::cout << "Game loop ended!" << std::endl;
}

void introPage(Window& window, std::vector<Button>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame) {
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);

    // Rendre la frame GIF en plein écran
    if (!gifFrames.empty()) {
        SDL_Texture* currentTexture = gifFrames[currentFrame];
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
        window.renderTexture(currentTexture, 0, 0, windowWidth, windowHeight);  // Plein écran
    }

    // Dessiner le texte par-dessus l'image
    window.drawText("PARK", 880, 50, 100);
    window.drawText("AND", 970, 150, 100);
    window.drawText("FURIOUS", 1050, 250, 100);

    for (Button& button : buttons) {
        button.draw();
    }
    SDL_RenderPresent(window.renderer);
}


