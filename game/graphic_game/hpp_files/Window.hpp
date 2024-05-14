// #ifndef WINDOW_HPP
// #define WINDOW_HPP

// #include <SDL2/SDL.h>

// class Window {
// private:
//     SDL_Window *window;
// public:
//     Window(const char* title, int width, int height);
//     ~Window();
//     bool isOpen();
// };

// #endif 
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    SDL_Window *introWindow;
    SDL_Window *menuWindow;
    SDL_Window *parkingWindow;
    int currentWindowState; // 0: Intro, 1: Menu, 2: Parking
public:
    Window(const char* introTitle, const char* menuTitle, const char* parkingTitle, int width, int height);
    ~Window();
    bool isOpen();
    void switchState(int newState);
    int getCurrentState();
};

#endif /* WINDOW_HPP */
