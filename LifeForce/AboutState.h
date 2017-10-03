/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#ifndef ABOUTSTATE_H_
#define ABOUTSTATE_H_

#include "GameState.h"
#include "GameStateEnum.h"

class AboutState : public GameState {
public:
	AboutState();
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