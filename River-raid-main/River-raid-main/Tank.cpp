#include "Tank.h"
#include "Game.h"
#include "GameConfig.h"
#include <cstdlib> // For rand()

Tank::Tank() : Enemy() {}

Tank::Tank(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2) :
    Enemy(g, ref, w, h, fc, bc, c1, c2) {
    const int min = (int)(config.windowWidth * config.ratio);
    const int max_minus_min = (int)(config.windowWidth * (1 - config.ratio) - 100 - 1 - config.windowWidth * config.ratio);
    int x = min + rand() % max_minus_min;
    setX(x);
    setY(config.toolBarHeight);
}

void Tank::draw() const {
    window* pWind = pGame->getWind(); // Access the window pointer from the Game instance

    float hratio = (float)getHeight() / 220.0;
    float wratio = (float)getWidth() / 650.0;

    pWind->SetPen(getBorderColor());
    pWind->SetBrush(getColor1());
    pWind->DrawRectangle(getX() + (int)(50 * wratio), getY() + (int)(170 * hratio), getX() + (int)(420 * wratio), getY() + (int)(220 * hratio));

    pWind->SetBrush(getColor2());
    pWind->DrawRectangle(getX(), getY() + (int)(170 * hratio), getX() + getWidth(), getY() + (int)(120 * hratio));

    pWind->SetBrush(getFillColor());
    pWind->DrawRectangle(getX() + (int)(50 * wratio), getY() + (int)(120 * hratio), getX() + (int)(420 * wratio), getY() + (int)(90 * hratio));
    pWind->DrawRectangle(getX() + (int)(70 * wratio), getY() + (int)(90 * hratio), getX() + (int)(380 * wratio), getY() + (int)(60 * hratio));
    pWind->DrawRectangle(getX() + (int)(300 * wratio), getY() + (int)(60 * hratio), getX() + (int)(380 * wratio), getY());
}

void Tank::move() {
    int speed = pGame->getEnemySpeed();
    // Tanks move down and slightly side to side
    setY(getY() + speed);
    
}

string Tank::getType() const {
    return "Tank";
}