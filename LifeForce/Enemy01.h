/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-28
Project: Introduction to game programming in windows, project assignment

desc:
Enemy 01
************************************************************************/

#ifndef ENEMY01_H_
#define ENEMY01_H_

#include "..\Engine\GameEngine.h"
#include "Enemy.h"

using namespace GameEngine;

class Enemy01 : public Enemy {
public:
	Enemy01(std::string filename, int startPosX, int startPosY, bool hasPowerUp = false, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
	void update();
};

#endif