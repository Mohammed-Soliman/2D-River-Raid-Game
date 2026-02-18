#pragma once
#pragma once
#include "Enemy.h"

class Jet : public Enemy
{
public:
    Jet();
	Jet(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2);
    void draw() const override;
    void move()  override;
    string getType() const override;
};
