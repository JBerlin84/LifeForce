/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-28
Project: Introduction to game programming in windows, project assignment

desc:
Enemy 02
************************************************************************/

#ifndef ENEMY02_H_
#define ENEMY02_H_

#include <cmath>

#include "..\Engine\GameEngine.h"
#include "Enemy.h"

using namespace GameEngine;

#define OSCILLATION_SPEED 0.05
#define OSCILLATION_STRENGTH 100
#define X_SPEED 4

class Enemy02 : public Enemy {
public:
	Enemy02(std::string filename, int startPosX, int startPosY, bool hasPowerUp = false, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
	void update();
private:
	int originY;
	double yArg;
	double oscillationSpeed;
};

#endif