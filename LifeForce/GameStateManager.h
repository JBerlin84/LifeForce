/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Gamestatemanager holds the gamestate of the game. Manages switches
between different levels.
Tells the game what to do.
************************************************************************/

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include "GameState.h"
#include "GameStateEnum.h"
#include "MenuState.h"
#include "LevelStateBase.h"
#include "VictoryState.h"
#include "DefeatState.h"
#include "AboutState.h"
#include "Player.h"

class GameStateManager {
public:
	GameStateManager();
	void setState(state);
	void draw();
	void keyPressed(int k);
	void keyReleased(int k);
	void update();
	void release();
	
private:
	state currentState;
	vector<GameState*> gameStates;
	Player *player1;
	Player *player2;
	bool *twoPlayers;
	bool loadingScreenIsDisplaying;
};

#endif