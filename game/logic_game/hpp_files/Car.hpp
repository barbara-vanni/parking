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
};

#endif
