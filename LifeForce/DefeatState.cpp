/************************************************************************
Author: Jimmy Berlin
Last modified: 2016-01-10
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#include "DefeatState.h"

DefeatState::DefeatState() {
	background = NULL;
}

bool DefeatState::init(int width, int height) {

	gameBoardWidth = width;
	gameBoardHeight = height;

	// "init" background
	background = new GameObject();
	if (!background->loadImage("Resources\\Levels\\Defeat\\Background.jpg")) {
		engine->message("Error loading background");
	}
	
	// init music
	music = engine->LoadSound("Resources\\Levels\\Defeat\\Music.Wav");
	engine->LoopSound(music);

	letterPosition = 1080;
	letterSpeed = 1.5f;

	gameStateChanged = false;

	return true;
}

void DefeatState::update() {
	letterPosition -= letterSpeed;
}

void DefeatState::keyPressed(int k) {
	if (k == DIK_SPACE) {
		setNewGameState(menuState);	// new game
	}
}

void DefeatState::keyReleased(int k) {

}

void DefeatState::draw() {
	background->draw();

	const int numberOfElements = 50;

	// TODO: FIXA DETTA DJÄVULSKAPET
	std::string about[numberOfElements] = {
		"GAME OVER!!!",
		"",
		"",
		"UNFORTUNATELY YOU WHERE NOT MAN ENOUGH",
		"TO DEFEND THE EARTH FROM THE INVADING",
		"ALIENS",
		"",
		"MAYBE YOU SHOULD NOT HAVE EATEN ALL THE",
		"CHIPS AND SODA YOU BOUGHT, BUT INSTEAD",
		"MADE SOME REAL TRAINING.",
		"",
		"JUST BECAUSE OF YOUR BAD CHARACTER",
		"ALL OF EARTH IS NOW SUFFERING!",
		"",
		"SHAME ON YOU!!!",
	};

	for (int i = 0; i < numberOfElements; i++) {
		std::string s = about[i];
		int yPos = 100;
		font->setScale(1 * engine->getScreenScale());
		if (i == 0) {
			font->setScale(2 * engine->getScreenScale());
			yPos = 300;
		}
		font->Print((int)(yPos * engine->getScreenScale()), (int)((letterPosition + 64 * i) * engine->getScreenScale()), s.c_str(), 0xFFFFFFFF);
	}
}

void DefeatState::release() {
	music->Stop();
	delete music;
	delete background;
}

