#pragma once
#include "Background.h"

class Tree : public Background
{
private:
    color leevesColor;
public:
    Tree();
	Tree(Game* g, point p, int w, int h, color lc, color fc, color bc);
    void draw() const override;
    void move() override;
    void setLeevesColor(color c) { leevesColor = c; }
};
