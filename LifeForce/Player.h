/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Holds the player in the game
************************************************************************/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "..\Engine\GameEngine.h"

using namespace GameEngine;

class Player : public GameObject {
public:
	Player(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
	void update();
	void draw();
	void setPlayer2();
	void goLeft(bool value); void goRight(bool value); void goUp(bool value); void goDown(bool value);
	void setRateOfFire(int rate);
	void resetPosition();
	int getRateOfFire();
	void addPoints(int pointsToAdd);
	int getPoints();
	Timer* getFireTimer();
	bool getImmortal();
	int getHp();
	int getMaxHp();
	void setHp(int hp);
	bool hit();
	Texture* getPlayerDebris();
	Texture* getExplosion();
	Texture* getMissile();
	float getMissileSpeed();
	CSound* getMissileSound();
	CSound* getMissileExplosionSound();

private:
	Texture* playerDebris;
	Texture* explosion;
	Texture* missile;
	CSound* missileSound;
	CSound* missileExplosionSound;
	void	 clampToScreen();
	int		 rateOfFire;
	float	 missileSpeed;
	int      points;
	bool     immortal;
	Timer*   fireTimer;
	int		 immortalTime;
	Timer*   immortalTimer;
	Timer*	 flickerTimer;
	int		 flickerSpeed;
	bool	 displayFlicker;
	bool	 player2;
	int		 hp;
	int		 maxHp;

	bool up, down, left, right;
};

#endif