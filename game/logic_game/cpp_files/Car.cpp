#include <iostream>
#include "../hpp_files/GameObject.hpp"
#include "../../Grid.hpp"
#include "../hpp_files/Car.hpp"

Car::~Car() {}

void Car::move(int distance) {
    // Implémentation du mouvement général
}

void Car::moveUp() {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() - 1;
        if (withinLimits(getPosX(), newPosY)) {
            setPosY(newPosY);
        }
    }
}

void Car::moveDown() {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() + 1;
        if (withinLimits(getPosX(), newPosY)) {
            setPosY(newPosY);
        }
    }
}

void Car::moveLeft() {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() - 1;
        if (withinLimits(newPosX, getPosY())) {
            setPosX(newPosX);
        }
    }
}

void Car::moveRight() {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() + 1;
        if (withinLimits(newPosX, getPosY())) {
            setPosX(newPosX);
        }
    }
}

void Car::resetPosition() {
    setPosX(initialPosX);
    setPosY(initialPosY);
    std::cout << "Car reset to initial position: (" << initialPosX << ", " << initialPosY << ")" << std::endl; // Debug message
}

bool Car::withinLimits(int newPosX, int newPosY) const {
    if (isHorizontalOrientation()) {
        // Vérifie si la voiture horizontale dépasse les limites
        return newPosX >= 0 && (newPosX + getWidth() - 1) < maxCol && newPosY >= 0 && newPosY < maxRow;
    } else {
        // Vérifie si la voiture verticale dépasse les limites
        return newPosX >= 0 && newPosX < maxCol && newPosY >= 0 && (newPosY + getHeight() - 1) < maxRow;
    }
}



