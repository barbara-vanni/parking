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
    State currentState;
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Window(const char* title, int width, int height);
    ~Window();
    // bool isOpen();
    void switchState(State newState);
    State getCurrentState();
    void drawText(const std::string &text, int x, int y, int size);
};

#endif

