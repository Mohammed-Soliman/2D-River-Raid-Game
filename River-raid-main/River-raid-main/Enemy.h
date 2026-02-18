#pragma once
#include "GameObject.h"

class Game; // Forward declaration

class Enemy : public GameObject
{
private:
    color color1, color2;
    bool checkMax;

public:
    Enemy();
    Enemy(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2);
    virtual ~Enemy();

    void setCheckMax(bool c);
    bool getCheckMax() const;

    void setSize(int w, int h);
    int getWidth() const;
    int getHeight() const;

    void setColors(color c1, color c2);
    color getColor1() const;
    color getColor2() const;

    virtual void draw() const = 0; // Pure virtual draw function
    virtual void move() = 0; // Move function to change position
    virtual string getType() const = 0; // Function to get the type of enemy
};

