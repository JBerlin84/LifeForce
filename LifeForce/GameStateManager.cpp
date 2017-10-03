/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Gamestatemanager holds the gamestate of the game. Manages switches
between different levels.
Tells the game what to do.
************************************************************************/

#include "GameStateManager.h"

GameStateManager::GameStateManager() {
	
	currentState = menuState;
	player1 = new Player("resources\\Player.png");
	player2 = new Player("resources\\Player2.png");

	loadingScreenIsDisplaying = false;
	twoPlayers = new bool;

	gameStates.push_back(new MenuState(player1, player2, twoPlayers));
	gameStates.push_back(new LevelStateBase(player1, player2, twoPlayers, level1State));
	gameStates.push_back(new LevelStateBase(player1, player2, twoPlayers, level2State));
	gameStates.push_back(new LevelStateBase(player1, player2, twoPlayers, level3State));
	gameStates.push_back(new LevelStateBase(player1, player2, twoPlayers, level4State));
	gameStates.push_back(new LevelStateBase(player1, player2, twoPlayers, level5State));
	gameStates.push_back(new VictoryState());
	gameStates.push_back(new DefeatState());
	gameStates.push_back(new AboutState());
}

void GameStateManager::setState(state s) {
	currentState = s;
	gameStates[(int)currentState]->init();
}

void GameStateManager::keyPressed(int k) {
	gameStates[(int)currentState]->keyPressed(k);
}

void GameStateManager::keyReleased(int k) {
	gameStates[(int)currentState]->keyReleased(k);
}

void GameStateManager::draw() {
	gameStates[(int)currentState]->draw();
}

void GameStateManager::update() {
	// check if current state has changed, in that case, change it.
	// Make sure loading screen is displaying first before starting to load.
	if (gameStates[(int)currentState]->isGameStateChanged()) { // && loadingScreenIsDisplaying) {
		// release old state, and initialize new state.
		gameStates[(int)currentState]->release();
		setState(gameStates[(int)currentState]->getNewGameState());
		loadingScreenIsDisplaying = false;
	}
	gameStates[(int)currentState]->update();
	
}

void GameStateManager::release() {
	gameStates[(int)currentState]->release();
}