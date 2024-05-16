#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject {
public:
    GameObject(int posX, int posY, int width, int height, bool horizontalOrientation);
    int getPosX() const;
    int getPosY() const;
    int getWidth() const;
    int getHeight() const;
    bool isHorizontalOrientation() const;
    void setPosX(int posX) { this->posX = posX; };
    void setPosY(int posY) { this->posY = posY; };
    // ~GameObject() {};

private:
    int posX;
    int posY;
    int width;
    int height;
    bool horizontalOrientation;
};

#endif
