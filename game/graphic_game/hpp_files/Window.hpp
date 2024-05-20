#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
    SDL_Texture* loadTexture(const std::string &file);
    void renderTexture(SDL_Texture* tex, int x, int y, int w, int h);
    std::vector<SDL_Texture*> loadGifFrames(const std::string &path, int frameCount);
};

#endif
