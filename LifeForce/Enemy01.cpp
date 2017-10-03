/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-28
Project: Introduction to game programming in windows, project assignment

desc:
Enemy 01
************************************************************************/

#include "Enemy01.h"

Enemy01::Enemy01(std::string filename, int startPosX, int startPosY, bool hasPowerUp, D3DCOLOR transcolor)
	: Enemy(filename, startPosX, startPosY, hasPowerUp, transcolor) {
}

void Enemy01::update() {
	setX(getX() - 5);
}
