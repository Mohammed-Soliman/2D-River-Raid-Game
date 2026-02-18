#include "statusbar.h"
#include "statusbar.h"
#include "Game.h"
statusbar::statusbar(Game* r_pGame, point r_point, int r_width, int r_height) : Toolbar(r_pGame, r_point, r_width, r_height)
{
    //pW = r_pGame->getWind();
    penColor = YELLOW;
    y = r_point.y; //+ r_height / 2;
    points = 0;
    speed = 0;
    lives = 5;
    fuel = 50;
}
void statusbar::SetValues(int p, int s, int l, int f)
{
    points = p;
    speed = s;
    lives = l;
    fuel = f;
}
void statusbar::draw() const
{
	window* pW = pGame->getWind();
    int inBetween = (pW->GetWidth() - 2 * leftMargin) / 4;
    pW->SetPen(penColor, 3);
    pW->SetFont(20, BOLD, BY_NAME, "Arial");
    pW->DrawString(leftMargin, y + verticalOffset, "Points: " + to_string(points));
    pW->DrawString(leftMargin + inBetween, y + verticalOffset, "Speed: " + to_string(speed));
    pW->DrawString(leftMargin + 2 * inBetween, y + verticalOffset, "Lives: " + to_string(lives));
    pW->DrawString(leftMargin + 3 * inBetween, y + verticalOffset, "Fuel Gauge:" + to_string(fuel));
}
int statusbar::getPoints() const
{
    return points;
}
int statusbar::getSpeed() const
{
    return speed;
}
int statusbar::getLives() const
{
    return lives;
}
int statusbar::getFuel() const
{
    return fuel;
}