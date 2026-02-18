#include "FuelDepot.h"
#include "Game.h"

FuelDepot::FuelDepot() : GameObject() {}
FuelDepot::FuelDepot(Game* g, point ref, int w, int h, color cf, color cb) : GameObject(g, ref, w, h, cf, cb) {}

void FuelDepot::draw() const {
    window* pWind = pGame->getWind();
    if (!pWind) return;

    // Draw the depot body
    pWind->SetPen(BLACK, 2);
    pWind->SetBrush(YELLOW);
    pWind->DrawRectangle(getX(), getY(), getX() + getWidth(), getY() + getHeight(), FILLED);

    // Draw "FUEL" text
    pWind->SetPen(BLACK);
    pWind->SetFont(14, BOLD, BY_NAME, "Arial");
    pWind->DrawString(getX() + 5, getY() + getHeight()/4, "FUEL");
}

void FuelDepot::move() {
    int speed = pGame->getBackgroundSpeed();
    setY(getY() + speed);
}

