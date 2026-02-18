#pragma once
#include "Background.h"
#include "Game.h"

class Background;

class Bridge : public Background
{
public:
    Bridge();
	Bridge(Game* g, point p, int w, int h, color fc, color bc);
    void draw() const override;
    void move() override;
};
