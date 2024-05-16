#include "../hpp_files/GameObject.hpp"
#include "../../Grid.hpp"
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
    if (!isHorizontalOrientation()) {
        setPosY(getPosY() - 1);
    }
}

void Car::moveDown() {
    if (!isHorizontalOrientation()) {
        setPosY(getPosY() + 1);
    }
}

void Car::moveLeft() {
    if (isHorizontalOrientation()) {
        setPosX(getPosX() - 1);
    }
}

void Car::moveRight() {
    if (isHorizontalOrientation()) {
        setPosX(getPosX() + 1);
    }
}
