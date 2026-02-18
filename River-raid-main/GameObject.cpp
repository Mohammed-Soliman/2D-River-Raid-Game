#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : Drawable(r_pGame, ref, r_width, r_height)
{
	fillColor = fc;
	borderColor = bc;
}

GameObject::GameObject()
{
}

void GameObject::setRefPoint(point p)
{
	RefPoint = p;
}



void GameObject::setX(int x) { RefPoint.x = x; }
void GameObject::setY(int y) { RefPoint.y = y; }
int GameObject::getX() const { return RefPoint.x; }
int GameObject::getY() const { return RefPoint.y; }

int GameObject::getWidth() const { return width; }
int GameObject::getHeight() const { return height; }

void GameObject::setSize(int w, int h)
{
	width = w;
	height = h;
}

color GameObject::getFillColor() const
{
	return fillColor;
}

color GameObject::getBorderColor() const
{
	return borderColor;
}

void GameObject::setFillColor(color fc)
{
	fillColor = fc;
}

void GameObject::setBorderColor(color bc)
{
	borderColor = bc;
}
