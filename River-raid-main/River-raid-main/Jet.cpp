#include "Jet.h"
#include "GameConfig.h"   // For time()
#include "Game.h"
#include "GameObject.h"

#include "GameConfig.h"
#include <cstdlib> // For rand()

Jet::Jet() : Enemy() {}

Jet::Jet(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2) :
	Enemy(g, ref, w, h, fc, bc, c1, c2) {
    int x = rand() % 2; // Randomly choose to move left or right
    if (x == 0)
        setX(0); // Start from the left
    else
        setX(config.windowWidth); // Start from the right

    int y = 0 + rand() % 350; // Randomly choose a vertical position
    setY(y);
	
}

void Jet::draw() const
{
    window* pWind = pGame->getWind(); // Access the window pointer from the Game instance

    float hratio = (float)getHeight() / 500.0;
    float wratio = (float)getWidth() / 620.0;

    pWind->SetBrush(getColor1());
    pWind->DrawRectangle(getX() + int(250 * wratio), getY(), getX() + int(320 * wratio), getY() + int(500 * hratio));

    int coor_x1_wings[4] = { getX() + int(250 * wratio), getX(), getX(), getX() + int(250 * wratio) };
    int coor_y_wings[4] = { getY() + int(450 * hratio), getY() + int(250 * hratio), getY() + int(100 * hratio), getY() + int(300 * hratio) };
    pWind->DrawPolygon(coor_x1_wings, coor_y_wings, 4);

    int coor_x2_wings[4] = { getX() + int(320 * wratio), getX() + int(620 * wratio), getX() + int(620 * wratio), getX() + int(320 * wratio) };
    pWind->DrawPolygon(coor_x2_wings, coor_y_wings, 4);

    int coor_x1_tail[4] = { getX() + int(250 * wratio), getX() + int(100 * wratio), getX() + int(100 * wratio), getX() + int(250 * wratio) };
    int coor_y_tail[4] = { getY() + int(150 * hratio), getY() + int(100 * hratio), getY() + int(80 * hratio), getY() + int(30 * hratio) };
    pWind->DrawPolygon(coor_x1_tail, coor_y_tail, 4);

    int coor_x2_tail[4] = { getX() + int(320 * wratio), getX() + int(470 * wratio), getX() + int(470 * wratio), getX() + int(320 * wratio) };
    pWind->DrawPolygon(coor_x2_tail, coor_y_tail, 4);
}


void Jet::move() {
    int speed = pGame->getEnemySpeed() * 1.5;  // Jets are faster
    // Determine if jet is moving left or right based on initial position
    if (getX() > config.windowWidth) {
        setX(getX() - speed);  // Moving left
    } else {
        setX(getX() + speed);  // Moving right
    }

    setY(getY() + speed);  // Move downwards as well
}
string Jet::getType() const {
    return "Jet";
}