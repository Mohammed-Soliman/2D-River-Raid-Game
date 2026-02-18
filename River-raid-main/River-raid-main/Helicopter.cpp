#include "Helicopter.h"
#include "GameConfig.h"   // For time()

#include <cstdlib> // For rand()
#include <cmath>   // For sin()

//const double ratio = 0.2;	//Ratio of the playing area to the window height
//int	windWidth = 1200; int windHeight = 600;

Helicopter::Helicopter() : Enemy() {}

Helicopter::Helicopter(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2) :
	Enemy(g, ref, w, h, fc, bc, c1, c2) {
    const int min = (int)(config.windowWidth * config.ratio);
    const int max_minus_min = (int)(config.windowWidth * (1 - config.ratio) - 100 - 1 - config.windowWidth * config.ratio);

    int x = min + rand() % max_minus_min;
    int condition = rand() % 2;

    if (condition == 0) {
        setX(x);
        setCheckMax(true);
    }
    else {
        setX(x);
        setCheckMax(false);
    }
    setY(0);

}

void Helicopter::draw() const {
    float hratio = (float)getHeight() / 340.0;
    float wratio = (float)getWidth() / 600.0;

	window* pWind = pGame->getWind();

    pWind->SetBrush(getBorderColor());
    pWind->DrawRectangle(getX(), getY() + (int)(145 * hratio), getX() + getWidth(), getY() + (int)(195 * hratio));
    pWind->SetPen(getBorderColor());
    pWind->SetBrush(getColor2());
    pWind->DrawCircle(getX() + (int)(400 * wratio), getY() + (int)(170 * hratio), 100 * hratio);
    pWind->SetBrush(getColor1());
    pWind->DrawRectangle(getX() + (int)(20 * wratio), getY() + (int)(215 * hratio), getX() + (int)(50 * wratio), getY() + (int)(125 * hratio));
    pWind->DrawRectangle(getX() + (int)(385 * wratio), getY() + (int)(340 * hratio), getX() + (int)(415 * wratio), getY() + (int)(270 * hratio));
    pWind->DrawRectangle(getX() + (int)(325 * wratio), getY() + (int)(335 * hratio), getX() + (int)(475 * wratio), getY() + (int)(300 * hratio));
    pWind->SetBrush(getFillColor());
    pWind->DrawRectangle(getX() + (int)(230 * wratio), getY() + (int)(40 * hratio), getX() + (int)(570 * wratio), getY() + (int)(10 * hratio));
    pWind->DrawRectangle(getX() + (int)(385 * wratio), getY() + (int)(70 * hratio), getX() + (int)(415 * wratio), getY());
}


void Helicopter::move() {
    int speed = pGame->getEnemySpeed();

    setY(getY() + speed); // Move vertically down
    if (getCheckMax()) {
        if (getX() <= config.windowWidth * config.ratio)
            setCheckMax(false);
        else
            setX(getX() - speed); // Move left
    }
    else {
        if (getX() >= config.windowWidth * (1 - config.ratio) - getWidth())
            setCheckMax(true);
        else
            setX(getX() + speed); // Move right
    }
}

string Helicopter::getType() const {
    return "Helicopter";
}

