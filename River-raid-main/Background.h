#pragma once
#include "GameObject.h"

class Game; // Forward declaration

class Background : public GameObject
{
public:
	Background(Game* g, point p, int w, int h, color fc, color bc);
    Background();
    virtual ~Background();

    void setSize(int w, int h);
    int getWidth() const;
    int getHeight() const;
    

    virtual void draw() const = 0; // Pure virtual draw function
    virtual void move() = 0; // Pure virtual move function
};



