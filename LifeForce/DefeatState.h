/************************************************************************
Author: Jimmy Berlin
Last modified: 2016-01-10
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#ifndef DEFEATSTATE_H_
#define DEFEATSTATE_H_

#include "GameState.h"
#include "GameStateEnum.h"

class DefeatState : public GameState {
public:
	DefeatState();
	bool init(int width, int height);
	void draw();
	void update();
	void keyPressed(int k);
	void keyReleased(int k);
	void release();
private:
	bool isButtonRepeat;
	bool pressedOnce;
	CSound *music;
	float letterPosition;
	float letterSpeed;
	int characterWidth;
};

#endif