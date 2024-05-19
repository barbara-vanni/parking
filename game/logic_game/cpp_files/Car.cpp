#include <iostream>
#include "../hpp_files/GameObject.hpp"
#include "../../Grid.hpp"
#include "../hpp_files/Car.hpp"

Car::~Car() {}

void Car::move(int distance) {
    // Implémentation du mouvement général
}

void Car::moveUp() {
    int newPosY = getPosY() - 1;
    if (withinLimits(getPosX(), newPosY)) {
        setPosY(newPosY);
    }
}

void Car::moveDown() {
    int newPosY = getPosY() + 1;
    if (withinLimits(getPosX(), newPosY)) {
        setPosY(newPosY);
    }
}

void Car::moveLeft() {
    int newPosX = getPosX() - 1;
    if (withinLimits(newPosX, getPosY())) {
        setPosX(newPosX);
    }
}

void Car::moveRight() {
    int newPosX = getPosX() + 1;
    if (withinLimits(newPosX, getPosY())) {
        setPosX(newPosX);
    }
}

void Car::resetPosition() {
    setPosX(initialPosX);
    setPosY(initialPosY);
    std::cout << "Car reset to initial position: (" << initialPosX << ", " << initialPosY << ")" << std::endl; // Debug message
}

bool Car::withinLimits(int newPosX, int newPosY) const {
    // Vérifie si les nouvelles positions sont dans les limites de la grille
    if (newPosX < 0 || newPosX >= maxCol -1|| newPosY < 0 || newPosY >= maxRow) {
        return false;
    }
    return true;
}


