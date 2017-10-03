/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-28
Project: Introduction to game programming in windows, project assignment

desc:
Enemy 02
************************************************************************/

#include "Enemy02.h"

Enemy02::Enemy02(std::string filename, int startPosX, int startPosY, bool hasPowerUp, D3DCOLOR transcolor)
	: Enemy(filename, startPosX, startPosY, hasPowerUp, transcolor) {
	yArg = startPosX;		// just to make them a bit irregular.
	originY = startPosY;
}

void Enemy02::update() {

	yArg += OSCILLATION_SPEED;

	setX(getX() - X_SPEED);
	setY(originY + std::sin(yArg) * OSCILLATION_STRENGTH);
}
