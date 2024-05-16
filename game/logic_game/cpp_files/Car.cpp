#include "../hpp_files/GameObject.hpp"
#include "../hpp_files/Car.hpp"

Car::Car(int posX, int posY, int width, int height, bool horizontalOrientation) 
    : GameObject(posX, posY, width, height, horizontalOrientation) {}

// Car::~Car() {}

void Car::move(int distance) {
    if (isHorizontalOrientation()) {
        setPosX(getPosX() + distance);
    } else {
        setPosY(getPosY() + distance);
    }

}