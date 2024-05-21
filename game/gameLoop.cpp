#include "gameLoop.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include "logic_game/hpp_files/StockCar.hpp"
#include "graphic_game/hpp_files/Button.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Main game loop for running the game, handling events and rendering


void mainLoop(Window& window, Grid& grid, std::vector<Button*>& buttons, StockCar& stockCar, int& selectedCarIndex) {
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

    std::vector<SDL_Texture*> gifFrames = window.loadGifFrames("assets/images", 52);  
    int currentFrame = 0;
    Uint32 lastGifFrameTime = 0;
    const Uint32 gifFrameDelay = 60;  

    while (gameisrunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameisrunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;

                        if (window.getCurrentState() == State::Intro) {
                            if (buttons[0]->isClickedAtPosition(x, y)) {
                                buttons[0]->click();
                                window.switchState(State::Menu);
                                stateChanged = true;
                            }
                        } else if (window.getCurrentState() == State::Menu) {
                            for (Button* button : buttons) {
                                if (button->isClickedAtPosition(x, y)) {
                                    button->click();
                                    if (button == buttons[1]) {  
                                        window.switchState(State::Parking);
                                        stateChanged = true;
                                    }
                                }
                            }
                        } else if (window.getCurrentState() == State::Parking) {
                            for (int i = 0; i < stockCar.getStockCar().size(); ++i) {
                                Car& car = stockCar.getStockCar()[i];
                                int carX = car.getPosX() * 110;
                                int carY = car.getPosY() * 110;
                                int carW = car.isHorizontalOrientation() ? car.getWidth() * 100 : car.getHeight() * 100;
                                int carH = car.isHorizontalOrientation() ? car.getHeight() * 100 : car.getWidth() * 100;

                                if (x >= carX && x <= carX + carW && y >= carY && y <= carY + carH) {
                                    selectedCarIndex = i;
                                    grid.setSelectedCar(&car);
                                    break;
                                }
                            }
                        }
                    }
                    break;

        case SDL_KEYDOWN:
            if (window.getCurrentState() == State::Parking && selectedCarIndex != -1) {
                Car& selectedCar = stockCar.getStockCar()[selectedCarIndex];
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        selectedCar.moveUp(stockCar.getStockCar());
                        break;
                    case SDLK_DOWN:
                        selectedCar.moveDown(stockCar.getStockCar());
                        break;
                    case SDLK_LEFT:
                        selectedCar.moveLeft(stockCar.getStockCar());
                        break;
                    case SDLK_RIGHT:
                        selectedCar.moveRight(stockCar.getStockCar());
                        break;
                    default:
                        break;
                }

                if (selectedCar.getIsPlayer() && selectedCar.getPosX() == grid.getExitCol() - 1 && selectedCar.getPosY() == grid.getExitRow()) {
                    victory = true;
                }

                gridChanged = true;
            } else if (event.key.keysym.sym == SDLK_RETURN) {
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
            break;
    }

        }

        switch (window.getCurrentState()) {
            case State::Intro:
                if (SDL_GetTicks() - lastGifFrameTime > gifFrameDelay && currentFrame < gifFrames.size() - 1) {
                    currentFrame++;
                    lastGifFrameTime = SDL_GetTicks();
                }
                introPage(window, buttons, gifFrames, currentFrame);
                break;
            case State::Menu:
                menuPage(window, buttons);
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
                    window.drawText("Victory!", 900, 50, 100);
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
            stockCar.resetCars();

            for (Button* button : buttons) {
                button->resetClick();
            }

            window.switchState(State::Menu);
            victory = false;
            stateChanged = true;
        }
    }

    std::cout << "Game loop ended!" << std::endl;
}

void introPage(Window& window, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame) {
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);

    if (!gifFrames.empty()) {
        SDL_Texture* currentTexture = gifFrames[currentFrame];
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
        window.renderTexture(currentTexture, 0, 0, windowWidth, windowHeight);
    }

    window.drawText("PARK", 880, 50, 100);
    window.drawText("AND", 970, 150, 100);
    window.drawText("FURIOUS", 1050, 250, 100);

    if (!buttons.empty()) {
        buttons[0]->draw();
    }
    SDL_RenderPresent(window.renderer);
}


void menuPage(Window& window, std::vector<Button*>& buttons) {
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);

    SDL_Surface* backgroundSurface = IMG_Load("assets/images/menu.png");
    if (backgroundSurface == nullptr) {
        std::cerr << "Erreur lors du chargement de l'image de fond : " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(window.renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        std::cerr << "Erreur lors de la création de la texture de fond : " << SDL_GetError() << std::endl;
        return;
    }
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = windowWidth;
    destRect.h = windowHeight;

    SDL_RenderCopy(window.renderer, backgroundTexture, nullptr, &destRect);
    window.drawText("PARK", 620, 10, 100);
    window.drawText("AND", 850, 60, 100);
    window.drawText("FURIOUS", 1050, 110, 100);
    window.drawText("Choose your Level", 30, 400, 60);
    if (!buttons.empty()) {
        for (size_t i = 1; i < buttons.size(); ++i) {
            buttons[i]->draw();
        }
    }
    SDL_DestroyTexture(backgroundTexture);
    SDL_RenderPresent(window.renderer);
}