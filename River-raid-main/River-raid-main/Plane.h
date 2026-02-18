#pragma once
#include "GameObject.h"

class Plane : public GameObject
{
private:
    int fixed_position;
    int Wp;
public:
    Plane();
	Plane(Game* g, point ref, int w, int h, color fc, color bc);
    void draw() const override;
    void move() override;
};
