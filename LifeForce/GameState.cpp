/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
functions for the abstract class gameState
************************************************************************/

#include "GameState.h"

GameState::GameState() {
	font = new Font();
	if (!font->loadImage("resources\\Arcade.tga")) {
		engine->message("Error loading font");
	}
	font->setColumns(16);
	font->setTotalFrames(256);
	font->setCharSize(64, 63);
	if (!font->loadWidthData("resources\\Arcade.dat")) {
		engine->message("Error loading font data");
	}
}

bool GameState::isGameStateChanged() {
	return gameStateChanged;
}

void GameState::setNewGameState(state newGameState) {
	this->newGameState = newGameState;
	gameStateChanged = true;
}

state GameState::getNewGameState() {
	return newGameState;
}