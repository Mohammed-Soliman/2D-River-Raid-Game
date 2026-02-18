#pragma once
#pragma once
#include "Enemy.h"
#include "Game.h"

class Helicopter : public Enemy
{
public:
    Helicopter();
	Helicopter(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2);
    void draw() const override;
    void move() override;
    string getType() const override;
};

