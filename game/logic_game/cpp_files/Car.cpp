#include "../hpp_files/GameObject.hpp"
#include "../../Grid.hpp"
#include "../hpp_files/Car.hpp"

Car::Car(int posX, int posY, int width, int height, bool horizontalOrientation) 
    : GameObject(posX, posY, width, height, horizontalOrientation) {}

Car::~Car() {}


// void Car::move(int distance) {
//     if (isHorizontalOrientation()) {
//         setPosX(getPosX() + distance);
//     } else {
//         setPosY(getPosY() + distance);
//     }
// }

// void Car::moveUp() {
//     if (!isHorizontalOrientation()) {
//         setPosY(getPosY() - 1);
//     }
// }

// void Car::moveDown() {
//     if (!isHorizontalOrientation()) {
//         setPosY(getPosY() + 1);
//     }
// }

// void Car::moveLeft() {
//     if (isHorizontalOrientation()) {
//         setPosX(getPosX() - 1);
//     }
// }

// void Car::moveRight() {
//     if (isHorizontalOrientation()) {
//         setPosX(getPosX() + 1);
//     }
// }

void Car::move(int distance) {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() + distance;
        if (newPosX >= 0 && newPosX + getWidth() <= 6) {
            setPosX(newPosX);
        }
    } else {
        int newPosY = getPosY() + distance;
        if (newPosY >= 0 && newPosY + getHeight() <= 6) {
            setPosY(newPosY);
        }
    }
}

void Car::moveUp() {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() - 1;
        if (newPosY >= 0) {
            setPosY(newPosY);
        }
    }
}

void Car::moveDown() {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() + 1;
        if (newPosY + getHeight() <= 6) {
            setPosY(newPosY);
        }
    }
}

void Car::moveLeft() {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() - 1;
        if (newPosX >= 0) {
            setPosX(newPosX);
        }
    }
}

void Car::moveRight() {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() + 1;
        if (newPosX + getWidth() <= 6) {
            setPosX(newPosX);
        }
    }
}

