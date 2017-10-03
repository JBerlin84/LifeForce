/************************************************************************
Author: Jimmy Berlin
Last modified: 2016-01-10
Project: Game programming in windows II, project assignment

desc:
A game state
Victory state, this is the state you get to when you beat the game
************************************************************************/

#include "VictoryState.h"

VictoryState::VictoryState() {
	background = NULL;
}

bool VictoryState::init(int width, int height) {

	gameBoardWidth = width;
	gameBoardHeight = height;

	letterPosition = (float)(gameBoardHeight);
	letterSpeed = 1.2f;

	// "init" background
	background = new GameObject();
	if (!background->loadImage("Resources\\Levels\\Victory\\Background.jpg")) {
		engine->message("Error loading background");
	}

	
	// init music
	music = engine->LoadSound("Resources\\Levels\\Victory\\Music.Wav");
	engine->LoopSound(music);


	gameStateChanged = false;	// Reset flag
	pressedOnce = false;		// Press enter twice to get out of the screen

	gameStateChanged = false;

	saveCheckpoint();

	return true;
}

void VictoryState::saveCheckpoint() {
	std::ofstream state("Resources\\Savestate.dat");
	if (state.is_open()) {
		state << 1 << std::endl;
		state << 0 << std::endl;
		state.close();
	}
}

void VictoryState::update() {
	letterPosition -= letterSpeed;

	// Go back to menu state after text has passed.
	if (letterPosition < -(gameBoardHeight + 750)) {
		setNewGameState(menuState);
	}
}

void VictoryState::keyPressed(int k) {
	if (k == DIK_SPACE) {
		setNewGameState(menuState);	// new game
	}
}

void VictoryState::keyReleased(int k) {

}

void VictoryState::draw() {
	background->draw();

	const int numberOfElements = 50;

	// TODO: FIXA DETTA DJÄVULSKAPET
	std::string about[numberOfElements] = {
		"CONGRATULATIONS!!!",
		"",
		"",
		"THE INVASION HAS BEEN DESTROYED!",
		"",
		"YOU ALONE WAS STRONG ENOUGH TO TAKE",
		"DOWN THE ENEMY FORCE.",
		"",
		"I BET THEY REGRET",
		"TRYING TO INVADE",
		"THE EARTH!",
		"",
		"",
		"THANKS TO YOU,",
		"THE REST OF THE EARTHS POPULATION",
		"CAN LIVE IN PEACE!",
		"ALSO, I BET YOU WILL BE GREETED AS A",
		"TRUE HERO WHEN YOU GET BACK TO EARTH",
		"",
		"DON'T LET IT GET TO YOUR HEAD!!!",
		"THIS IS JUST A COMPUTER GAME!!!",
	};

	for (int i = 0; i < numberOfElements; i++) {
		std::string s = about[i];
		int yPos = (int)(100 * engine->getScreenScale());
		font->setScale(1 * engine->getScreenScale());
		if (i == 0) {
			font->setScale(2 * engine->getScreenScale());
			yPos = (int)(300 * engine->getScreenScale());
		}
		font->Print((int)(yPos * engine->getScreenScale()), (int)((letterPosition + 64 * i) * engine->getScreenScale()), s.c_str(), 0xFFFFFFFF);
	}
}

void VictoryState::release() {
	music->Stop();
	delete music;
	delete background;
}