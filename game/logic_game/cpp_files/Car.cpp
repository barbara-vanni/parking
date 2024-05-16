#include "../hpp_files/GameObject.hpp"
#include "../hpp_files/Car.hpp"

Car::Car(int posX, int posY, int width, int height, bool horizontalOrientation) 
    : GameObject(posX, posY, width, height, horizontalOrientation) {}

Car::~Car() {}

void Car::move(int distance) {
    if (isHorizontalOrientation()) {
        setPosX(getPosX() + distance);
    } else {
        setPosY(getPosY() + distance);
    }
}

void Car::moveUp() {
    setPosY(getPosY() - 1);
}

void Car::moveDown() {
    setPosY(getPosY() + 1);
}

void Car::moveLeft() {
    setPosX(getPosX() - 1);
}

void Car::moveRight() {
    setPosX(getPosX() + 1);
}