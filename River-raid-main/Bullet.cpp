#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() : GameObject() {}

Bullet::Bullet(Game* g, point p, int w, int h, color fc, color bc) 
    : GameObject(g, p, w, h, fc, bc) {}

void Bullet::draw() const {
    window* pWind = pGame->getWind();
    if (!pWind) return;

    // Draw bullet as a filled rectangle with outline
    pWind->SetPen(RED, 2);    // Red outline, 2 pixels thick
    pWind->SetBrush(YELLOW);  // Yellow fill
    pWind->DrawRectangle(getX(), getY(), getX() + getWidth(), getY() + getHeight(), FILLED);
}

void Bullet::move() {
    // Move upward faster
    setY(getY() - 10);  // Increased speed from BULLET_SPEED
}

bool Bullet::isOutOfBounds() const {
    return getY() <= MIN_Y;
}
