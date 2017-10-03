/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Holds the enemy in the game
************************************************************************/

#ifndef ENEMY_H_
#define ENEMY_H_

#include "..\Engine\GameEngine.h"

using namespace GameEngine;

class Enemy : public GameObject {
public:
	Enemy(std::string filename, int startPosX, int startPosY, bool hasPowerUp = false, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
	virtual void update() = 0;
	void draw();
	void hit();
	int getPoints();
	Texture* getEnemyDebris();
	Texture* getExplosion();

private:
	Texture* enemyDebris;
	Texture* explosion;
	int      points;
	bool	 hasPowerUp;
};

#endif