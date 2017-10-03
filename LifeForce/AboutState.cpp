/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#include "AboutState.h"

AboutState::AboutState() {
	background = NULL;
}

bool AboutState::init(int width, int height) {

	gameBoardWidth = width;
	gameBoardHeight = height;

	letterPosition = (float)(gameBoardHeight);
	letterSpeed = 1.2f;

	// "init" background
	background = new GameObject();
	if (!background->loadImage("Resources\\Levels\\About\\Background.jpg")) {
		engine->message("Error loading background");
	}

	// init music
	music = engine->LoadSound("Resources\\Levels\\Victory\\Music.Wav");
	engine->LoopSound(music);

	gameStateChanged = false;	// Reset flag
	pressedOnce = false;		// Press enter twice to get out of the screen

	return true;
}

void AboutState::update() {
	letterPosition -= letterSpeed;

	// Go back to menu state after text has passed.
	if (letterPosition < -(gameBoardHeight + 750)) {
		setNewGameState(menuState);
	}
}

void AboutState::keyPressed(int k) {
	if (k == DIK_SPACE) {
		setNewGameState(menuState);	// new game
	}
}

void AboutState::keyReleased(int k) {

}

void AboutState::draw() {
	background->draw();

	const int numberOfElements = 50;

	// TODO: FIXA DETTA DJÄVULSKAPET
	std::string about[numberOfElements] = {
		"LIFE FORCE",
		"",
		"",
		"A CLONE OF",
		"LIFE FORCE - SALAMANDER",
		"",
		"",
		"THE GAME WAS CREATED AS AN ASSIGNMENT",
		"IN GAME PROGRAMMING IN WINDOWS II ",
		"",
		"AN EXCITING COURSE TAKEN AT",
		"MID SWEDEN UNIVERSITY",
		"",
		"",
		"PROGRAMMING BY",
		"JIMMY BERLIN",
		"",
		"GRAPHICS BY",
		"CHRISTOPHER HOLGERSSON",
		"JIMMY BERLIN",
		"BACKGROUNDS FOR LEVELS ARE FROM GOOGLE",
		"AND TAGGED FOR REUSE",
		"",
		"MUSIC BY",
		"ANDREAS ROHDIN",
		"",
		"SOUND BY",
		"JIMMY BERLIN",
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

void AboutState::release() {
	music->Stop();
	delete music;
	delete background;
}