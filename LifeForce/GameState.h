/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
functions for the abstract class gameState
************************************************************************/

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "..\Engine\GameEngine.h"
#include "../Engine/GameEngine.h"
#include "GameStateEnum.h"

using namespace GameEngine;

class GameState {
public:
	GameState();
	virtual bool init(int width = 1920, int height = 1080) = 0;
	virtual void draw() = 0;
	virtual void keyPressed(int k) = 0;
	virtual void keyReleased(int k) = 0;
	virtual void update() = 0;
	virtual void release() = 0;
	bool isGameStateChanged();
	void setNewGameState(state newGameState);
	state getNewGameState();
protected:
	GameObject *background;
	GameObject *worldSprite;
	GameObject *explosion;
	bool gameStateChanged = false;	// If there is a new gamestate to go to, this is true;
	state newGameState;				// Sets the new gamestate to go to.
	int gameBoardWidth;
	int gameBoardHeight;
	Font *font;
};

#endif