#ifndef CAR_HPP
#define CAR_HPP
#include "GameObject.hpp"

class Car : public GameObject {
public:
    Car(int posX, int posY, int width, int height, bool horizontalOrientation, int maxRow, int maxCol, bool isPlayer = false)
        : GameObject(posX, posY, width, height, horizontalOrientation),
          initialPosX(posX), initialPosY(posY), maxRow(maxRow), maxCol(maxCol) {}

    ~Car();

    void move(int distance);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void resetPosition();
    bool getIsPlayer() const { return isPlayer; }

private:
    int initialPosX, initialPosY; // Positions initiales
    int maxRow, maxCol; // Limites de la grille
    bool isPlayer; // Indique si la voiture est le joueur
    bool withinLimits(int newPosX, int newPosY) const;
};

#endif
