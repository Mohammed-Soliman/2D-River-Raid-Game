#include "Enemy.h"



Enemy::Enemy()  {}
Enemy::Enemy(Game* g, point ref, int w, int h, color fc, color bc, color c1, color c2) : GameObject(g, ref, w, h, fc, bc), color1(c1), color2(c2) {}
Enemy::~Enemy() = default;



void Enemy::setCheckMax(bool c) { checkMax = c; }
bool Enemy::getCheckMax() const { return checkMax; }

void Enemy::setSize(int w, int h) { width = w; height = h; }
int Enemy::getWidth() const { return width; }
int Enemy::getHeight() const { return height; }

void Enemy::setColors(color c1, color c2) { color1 = c1; color2 = c2; }
color Enemy::getColor1() const { return color1; }
color Enemy::getColor2() const { return color2; }
