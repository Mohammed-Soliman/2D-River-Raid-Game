#pragma once
#include "Plane.h"
#include "GameConfig.h"   // For time()

#include "Jet.h"
#include "GameConfig.h"   // For time()
#include "Game.h"
#include "GameObject.h"

#include "GameConfig.h"
#include <cstdlib> // For rand()

Plane::Plane() : GameObject() {
    setBorderColor(YELLOW);
    setFillColor(YELLOW);
	setSize(100, 120);
}

Plane::Plane(Game* g, point ref, int w, int h, color fc, color bc) :
	GameObject(g, ref, w, h, fc, bc) {
	setBorderColor(YELLOW);
	setFillColor(YELLOW);
	setSize(100, 120);
    fixed_position = 200;
    Wp = (config.windowWidth / 2) - (getWidth() / 2);
    setX(Wp);
    setY(config.windowHeight - fixed_position);
}

void Plane::draw() const {
    window* pWind = pGame->getWind(); // Access the window pointer from the Game instance

    float hratio = (float)getHeight() / 500.0;
    float wratio = (float)getWidth() / 620.0;

    pWind->SetBrush(getFillColor());
    pWind->DrawRectangle(getX() + int(250 * wratio), getY() + int(500 * hratio), getX() + int(320 * wratio), getY());

    int coor_x1_wings[4] = { getX() + int(250 * wratio), getX(), getX(), getX() + int(250 * wratio) };
    int coor_y_wings[4] = { getY() + int(50 * hratio), getY() + int(250 * hratio), getY() + int(400 * hratio), getY() + int(200 * hratio) };
    pWind->DrawPolygon(coor_x1_wings, coor_y_wings, 4);

    int coor_x2_wings[4] = { getX() + int(320 * wratio), getX() + int(620 * wratio), getX() + int(620 * wratio), getX() + int(320 * wratio) };
    pWind->DrawPolygon(coor_x2_wings, coor_y_wings, 4);

    int coor_x1_tail[4] = { getX() + int(250 * wratio), getX() + int(100 * wratio), getX() + int(100 * wratio), getX() + int(250 * wratio) };
    int coor_y_tail[4] = { getY() + int(350 * hratio), getY() + int(400 * hratio), getY() + int(420 * hratio), getY() + int(470 * hratio) };
    pWind->DrawPolygon(coor_x1_tail, coor_y_tail, 4);

    int coor_x2_tail[4] = { getX() + int(320 * wratio), getX() + int(470 * wratio), getX() + int(470 * wratio), getX() + int(320 * wratio) };
    pWind->DrawPolygon(coor_x2_tail, coor_y_tail, 4);
}

void Plane::move() {
    window* pWind = pGame->getWind();
    int speed = pGame->getEnemySpeed();

    // Check for continuous key presses
    if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (getX() < config.windowWidth * (1 - config.ratio) - getWidth()) {
            setX(getX() + speed);
        }
    }
    if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (getX() > config.windowWidth * config.ratio) {
            setX(getX() - speed);
        }
    }
}
