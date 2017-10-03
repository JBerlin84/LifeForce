/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Menu state manages the main menu and the options menu
************************************************************************/

#include "MenuState.h"

MenuState::MenuState(Player *player1, Player *player2, bool *twoPlayers) {
	background = NULL;
	startMusic = true;
	this->twoPlayers = twoPlayers;
	this->player1 = player1;
	this->player2 = player2;
}

bool MenuState::init(int width, int height) {
	currentMenuChoice = 0;

	// "init" background
	background = new GameObject();
	if (!background->loadImage("Resources\\Levels\\Menu\\Background.jpg")) {
		engine->message("Error loading background");
	}

	gameStateChanged = false;	// Reset flag
	
	if (startMusic) {
		music = engine->LoadSound("Resources\\Levels\\Menu\\Music.wav");
		engine->LoopSound(music);
	}

	currentMenuState = main;
	isButtonRepeat = false;
	optionsIsFullscreen = engine->getFullscreen();							// set fullscreen
	optionsCurrentResolution = engine->getScreenWidth() == 1920 ? 1 : 0;		// set correct screen resolution

	return true;
}

void MenuState::update() {

}

void MenuState::keyPressed(int k) {
	if (k == DIK_UP && !isButtonRepeat) {
		--currentMenuChoice;
		if (currentMenuChoice < 0)
			currentMenuChoice = 0;
	}
	else if (k == DIK_DOWN && !isButtonRepeat) {
		++currentMenuChoice;
	}
	else if (k == DIK_RETURN  && !isButtonRepeat) {
		if (currentMenuState == main) {
			updateMainMenu();
		}
		else if (currentMenuState == options) {
			updateOptionsMenu();
		}
	}
	isButtonRepeat = true;
}

void MenuState::keyReleased(int k) {
	isButtonRepeat = false;
}

void ResetPlayer(Player *p) {
	p->setHp(p->getMaxHp());
	p->setAlive(true);
}

void MenuState::updateMainMenu() {
	switch (currentMenuChoice % 6) {
	case 0:
	{
		ResetPlayer(player1);
		if (*twoPlayers) {
			ResetPlayer(player2);
		}
		setNewGameState((state)fetchCurrentSavestate());
		break;
	}
	case 1:
		ResetPlayer(player1);
		*twoPlayers = false;
		setNewGameState(level1State);		// new game
		break;
	case 2:
		ResetPlayer(player1);
		ResetPlayer(player2);
		*twoPlayers = true;
		setNewGameState(level1State);		// new game
		break;
	case 3:
		setNewGameState(aboutState);		// about
		break;
	case 4:
		currentMenuState = options;
		currentMenuChoice = 0;
		break;
	case 5:
		engine->Shutdown();
	}
}

void MenuState::updateOptionsMenu() {
	switch (currentMenuChoice % 4) {
	case 0:
		optionsCurrentResolution++;
		optionsCurrentResolution %= 2;
		break;
	case 1:
		optionsIsFullscreen = !optionsIsFullscreen;
		break;
	case 2:
		saveConfig();
		currentMenuState = main;
		currentMenuChoice = 0;
		break;
	case 3:
		currentMenuState = main;
		currentMenuChoice = 0;
		break;
	}
}

int MenuState::fetchCurrentSavestate() {
	int level = -1;
	
	std::string line;
	std::ifstream state("Resources\\Savestate.dat");

	if (state.is_open()) {
		// Set world params
		getline(state, line);
		level = std::stoi(line);	// store world start position
		getline(state, line);
		*twoPlayers = std::stoi(line) == 1 ? true : false;		// store world end position

		state.close();
	}

	return level;
}

void MenuState::saveConfig() {

	std::string resolutions[] = { "1280x720", "1920x1080", "2560x1440", "3840x2160" };

	currentMenuChoice %= 4;
	std::string res = resolutions[optionsCurrentResolution];

	// Parse config
	// width
	size_t startPos = 0;
	size_t toCopy = res.find("x");
	std::string w = res.substr(startPos, toCopy);

	// height
	startPos = toCopy + 1;
	std::string h = res.substr(startPos);

	// store config
	std::ofstream config("Resources\\Config.cfg");
	if (config.is_open()) {
		config << (optionsIsFullscreen ? "true" : "false") << std::endl;
		config << w << std::endl;
		config << h << std::endl;
		config.close();
	}
}

void MenuState::draw() {
	background->draw();

	switch (currentMenuState)
	{
	case(main) :
		drawMainMenu();
		break;
	case(options) :
		drawOptionsMenu();
		break;
	default:
		break;
	}
}

void MenuState::drawMainMenu() {
	font->setScale(2.5 * engine->getScreenScale());
	font->Print(1, 1, "LIFE FORCE", 0xFFAAAAFF);
	font->setScale(1.2 * engine->getScreenScale());
	
	std::string menuItems[] = { "CONTINUE FROM LAST CHECKPOINT", "ONE PLAYER", "TWO PLAYER", "ABOUT", "OPTIONS", "EXIT" };

	for (int i = 0; i < 6; i++) {
		if (i == currentMenuChoice % 6) {
			std::string s = "[ " + menuItems[i] + " ]";
			font->Print((int)(40 * engine->getScreenScale()), (int)((500 + 100 * i) * engine->getScreenScale()), s.c_str(), 0xFFFFFFFF);
		}
		else {
			font->Print((int)((40 + font->getWidth()) * engine->getScreenScale()), (int)((500 + 100 * i) * engine->getScreenScale()), menuItems[i].c_str(), 0xFFFFFFFF);
		}
	}
}

void MenuState::drawOptionsMenu() {
	font->setScale(2.5f * engine->getScreenScale());
	font->Print(50, 50, "OPTIONS", 0xFFAAAAFF);
	font->setScale(1.2f * engine->getScreenScale());

	std::string menuItems[] = { "RESOLUTION", "FULLSCREEN", "SAVE", "CANCEL" };
	std::string resolutions[] = { "1280x720", "1920x1080" };

	for (int i = 0; i < 4; i++) {
		if (i == currentMenuChoice % 4) {
			std::string s = "[ " + menuItems[i] + " ]";
			font->Print((int)(40 * engine->getScreenScale()), (int)((500 + 100 * i) * engine->getScreenScale()), s.c_str(), 0xFFFFFFFF);
		}
		else {
			font->Print((int)((40 + font->getWidth()) * engine->getScreenScale()), (int)((500 + 100 * i) * engine->getScreenScale()), menuItems[i].c_str(), 0xFFFFFFFF);
		}
	}

	font->Print((int)(700 * engine->getScreenScale()), (int)(500 * engine->getScreenScale()), resolutions[optionsCurrentResolution].c_str(), 0xFFFFFFFF);
	font->Print((int)(700 * engine->getScreenScale()), (int)(600 * engine->getScreenScale()), optionsIsFullscreen ? "(X)" : "( )", 0xFFFFFFFF);

	font->setScale(0.6f * engine->getScreenScale());
	font->Print((int)(50 * engine->getScreenScale()), (int)(950 * engine->getScreenScale()), "NOTE - YOU HAVE TO RESTART THE GAME", 0xFFFFFFFF);
	font->Print((int)(50 * engine->getScreenScale()), (int)(1000 * engine->getScreenScale()), "FOR THE CHANGES TO TAKE EFFECT", 0xFFFFFFFF);

}

void MenuState::release() {
	music->Stop();
	delete music;
	delete background;
}

