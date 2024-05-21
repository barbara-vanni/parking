#include "../hpp_files/GameObject.hpp"
#include "../../Grid.hpp"
#include "../hpp_files/Car.hpp"

Car::~Car() {}

bool Car::isColliding(const Car& other) const {
    return !((getPosX() + getWidth() <= other.getPosX()) || (getPosX() >= other.getPosX() + other.getWidth()) ||
             (getPosY() + getHeight() <= other.getPosY()) || (getPosY() >= other.getPosY() + other.getHeight()));
}


void Car::move(int distance) {
    std::cout << "Move car by " << distance << " units" << std::endl;
}

void Car::moveUp(const std::vector<Car>& cars) {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() - 1;
        if (withinLimits(getPosX(), newPosY)) {
            bool collision = false;
            for (const auto& car : cars) {
                if (this != &car && car.isColliding(Car(getPosX(), newPosY, getWidth(), getHeight(), isHorizontalOrientation(), maxRow, maxCol))) {
                    collision = true;
                    break;
                }
            }
            if (!collision) {
                setPosY(newPosY);
            }
        }
    }
}

void Car::moveDown(const std::vector<Car>& cars) {
    if (!isHorizontalOrientation()) {
        int newPosY = getPosY() + 1;
        if (withinLimits(getPosX(), newPosY)) {
            bool collision = false;
            for (const auto& car : cars) {
                if (this != &car && car.isColliding(Car(getPosX(), newPosY, getWidth(), getHeight(), isHorizontalOrientation(), maxRow, maxCol))) {
                    collision = true;
                    break;
                }
            }
            if (!collision) {
                setPosY(newPosY);
            }
        }
    }
}

void Car::moveLeft(const std::vector<Car>& cars) {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() - 1;
        if (withinLimits(newPosX, getPosY())) {
            bool collision = false;
            for (const auto& car : cars) {
                if (this != &car && car.isColliding(Car(newPosX, getPosY(), getWidth(), getHeight(), isHorizontalOrientation(), maxRow, maxCol))) {
                    collision = true;
                    break;
                }
            }
            if (!collision) {
                setPosX(newPosX);
            }
        }
    }
}

void Car::moveRight(const std::vector<Car>& cars) {
    if (isHorizontalOrientation()) {
        int newPosX = getPosX() + 1;
        if (withinLimits(newPosX, getPosY())) {
            bool collision = false;
            for (const auto& car : cars) {
                if (this != &car && car.isColliding(Car(newPosX, getPosY(), getWidth(), getHeight(), isHorizontalOrientation(), maxRow, maxCol))) {
                    collision = true;
                    break;
                }
            }
            if (!collision) {
                setPosX(newPosX);
            }
        }
    }
}


void Car::resetPosition() {
    setPosX(initialPosX);
    setPosY(initialPosY);
    std::cout << "Car reset to initial position: (" << initialPosX << ", " << initialPosY << ")" << std::endl;
}

bool Car::withinLimits(int newPosX, int newPosY) const {
    if (isHorizontalOrientation()) {
        return newPosX >= 0 && (newPosX + getWidth() - 1) < maxCol && newPosY >= 0 && newPosY < maxRow;
    } else {
        return newPosX >= 0 && newPosX < maxCol && newPosY >= 0 && (newPosY + getHeight() - 1) < maxRow;
    }
}

