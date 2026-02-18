#pragma once
#pragma once
#include "toolbar.h"
class statusbar : public Toolbar
{
private:
    color penColor;
    int leftMargin = 100;
    int verticalOffset = 30;
    int integerSpacing = 175;
    int y;
    int points;
    int speed;
    int lives;
    int fuel;

public:
    statusbar(Game* r_pGame, point r_point, int r_width, int r_height);  // <<< Only DECLARATION here
    void draw() const override;
    void SetValues(int p, int s, int l, int f);
    int getPoints() const;
    int getSpeed() const;
    int getLives() const;
    int getFuel() const;
};

