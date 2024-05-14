#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>

enum class State {
    Intro,
    Menu,
    Parking
};

class Window {
private:
    SDL_Window *window;
    State currentState;
public:
    Window(const char* title, int width, int height);
    ~Window();
    bool isOpen();
    void switchState(State newState);
    State getCurrentState();
};

#endif

