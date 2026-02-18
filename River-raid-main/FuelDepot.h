#pragma once
#include "GameObject.h"

class Game; // Forward declaration

class FuelDepot : public GameObject
{
public:
    FuelDepot();
	FuelDepot(Game* g, point ref, int w, int h, color fc, color bc);
    void draw() const override;
    void move() override;
};

