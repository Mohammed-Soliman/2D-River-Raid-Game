#include "Bridge.h"
#include "GameConfig.h"


Bridge::Bridge() : Background() {}
Bridge::Bridge(Game* g, point p, int w, int h, color c1, color c2) : Background(g, p, w, h, c1, c2) {
	setX(p.x);
	setY(p.y);
	setSize(w, h);
}

void Bridge::draw() const {
	window* pWind = pGame->getWind(); // Access the window pointer from the Game instance
    pWind->SetBrush(getFillColor());
    pWind->DrawRectangle(config.ratio * config.windowWidth, getY(), config.windowWidth * (1 - config.ratio), getY() + getHeight());
}

void Bridge::move() {
	int speed = pGame->getBackgroundSpeed();
    setY(getY() + speed);
}

