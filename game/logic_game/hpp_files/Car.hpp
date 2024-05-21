#ifndef CAR_HPP
#define CAR_HPP
#include "GameObject.hpp"
#include <string>

// Car class declaration, child of GameObject

class Car : public GameObject {
public:
    Car(int posX, int posY, int width, int height, bool horizontalOrientation, int maxRow, int maxCol, bool isPlayer = false, const std::string& name = "")
        : GameObject(posX, posY, width, height, horizontalOrientation),
          initialPosX(posX), initialPosY(posY), maxRow(maxRow), maxCol(maxCol), isPlayer(isPlayer), name(name) {}

    ~Car();

    void move(int distance);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void resetPosition();
    bool getIsPlayer() const { return isPlayer; }
    std::string getName() const { return name; }

private:
    int initialPosX, initialPosY; 
    int maxRow, maxCol;
    bool isPlayer; 
    std::string name;
    bool withinLimits(int newPosX, int newPosY) const;
};

#endif
