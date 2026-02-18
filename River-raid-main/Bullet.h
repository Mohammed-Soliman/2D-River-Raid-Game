#pragma once
#include "GameObject.h"
#include "CMUgraphicsLib/CMUgraphics.h"

class Game; // Forward declaration

class Bullet : public GameObject {
private:
    const int BULLET_SPEED = 8; // Pixels per frame
    const int MIN_Y = 50;       // Minimum Y position (top of screen)

public:
    Bullet();
    Bullet(Game* g, point p, int w, int h, color fc, color bc);
    
    void draw() const override;
    void move() override;
    
    // Helper to check if bullet should be removed
    bool isOutOfBounds() const;
};
