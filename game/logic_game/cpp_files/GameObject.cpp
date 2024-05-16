#include "../hpp_files/GameObject.hpp"
#include <iostream>

GameObject::GameObject(int posX, int posY, int width, int height, bool horizontalOrientation) 
    : posX(posX), posY(posY), width(width), height(height), horizontalOrientation(horizontalOrientation) {}

GameObject::~GameObject() {}

int GameObject::getPosX() const { return posX; }
int GameObject::getPosY() const { return posY; }
int GameObject::getWidth() const { return width; }
int GameObject::getHeight() const { return height; }
bool GameObject::isHorizontalOrientation() const { return horizontalOrientation; }
