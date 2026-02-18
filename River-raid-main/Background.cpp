#include "Background.h"
#include "Game.h"



Background::Background(Game* g, point p, int w, int h, color fc, color bc) : GameObject(g, p, w, h, fc, bc) {}

Background::Background() {}

Background::~Background() = default;


void Background::setSize(int w, int h) { width = w; height = h; }
int Background::getWidth() const { return width; }
int Background::getHeight() const { return height; }



