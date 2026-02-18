#pragma once
#include "Tree.h"
#include "Game.h"
#include "GameConfig.h"

Tree::Tree() : Background() {}
Tree::Tree(Game* g, point p, int w, int h, color lc, color fc, color bc) : Background(g, p, w, h, fc, bc) {
    window* pWind = pGame->getWind();

    int choice_tree = rand() % 2;
    int tree_width = getWidth();
    int min = (int)(pWind->GetWidth() * config.ratio - 100);
    const int max_minus_min = (int)(pWind->GetWidth() * (1 - config.ratio) + tree_width);
    int x1 = tree_width / 4 + rand() % (min + 1);
    int x2 = max_minus_min + rand() % (pWind->GetWidth() - 100 - max_minus_min + 1);

    if (choice_tree == 0)
    {
        setX(x1);
    }
    else
    {
        setX(x2);
    }

	leevesColor = lc;
}

void Tree::draw() const {
    window* pWind = pGame->getWind(); // Access the window pointer from the Game instance

    float wratio = (float)getWidth() / 200.0;
    float hratio = (float)getHeight() / 350.0;

    pWind->SetPen(getBorderColor());
    pWind->SetBrush(getFillColor());
    pWind->DrawRectangle(getX() + (int)(65 * wratio), getY() + (int)(200 * hratio), getX() + (int)(135 * wratio), getY() + (int)(350 * hratio));

    pWind->SetBrush(leevesColor);
    pWind->DrawCircle(getX() + (int)(50 * wratio), getY() + (int)(120 * hratio), 100 * wratio);
    pWind->DrawCircle(getX() + (int)(150 * wratio), getY() + (int)(122 * hratio), 100 * wratio);
    pWind->DrawCircle(getX() + (int)(100 * wratio), getY() + (int)(50 * hratio), 100 * wratio);
}


void Tree::move() {
    int speed = pGame->getBackgroundSpeed();
    setY(getY() + speed);
}