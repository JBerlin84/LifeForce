/************************************************************************
Author: Jimmy Berlin
Last modified: 2016-01-10
Project: Game programming in windows II, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#ifndef VICTORYSTATE_H_
#define VICTORYSTATE_H_

#include "GameState.h"
#include "GameStateEnum.h"

class VictoryState : public GameState {
public:
	VictoryState();
	bool init(int width, int height);
	void draw();
	void update();
	void keyPressed(int k);
	void keyReleased(int k);
	void release();
private:
	void saveCheckpoint();
	bool isButtonRepeat;
	bool pressedOnce;
	CSound *music;
	float letterPosition;
	float letterSpeed;
	int characterWidth;
};

#endif