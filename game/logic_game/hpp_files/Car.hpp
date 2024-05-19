#ifndef CAR_HPP
#define CAR_HPP
#include "GameObject.hpp"

class Car : public GameObject {
public:
    Car(int posX, int posY, int width, int height, bool horizontalOrientation);
    ~Car();

    void move(int distance);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void resetPosition() {
        posX = initialPosX;
        posY = initialPosY;
    }

private:
    int posX, posY;
    int width, height;
    bool horizontalOrientation;
    int initialPosX, initialPosY;
};

#endif
