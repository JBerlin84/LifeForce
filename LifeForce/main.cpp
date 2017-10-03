/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-11-15
Project: Spelprogrammering i windows II, Project

desc:
main functions used with library GameEngine.
************************************************************************/

#include "main.h"

GameStateManager *gsm;

bool game_preload() {
	engine->setAppTitle(APPLICATION_TITLE);
	engine->setColorDepth(COLOR_DEPTH);

	// Read config file
	std::string line;
	std::ifstream config("Resources\\Config.cfg");
	if (config.is_open()) {
		// is fullscreen?
		getline(config, line);
		engine->setFullscreen((line.compare("true") == 0 || line.compare("1") == 0) ? true : false);

		//screen size
		getline(config, line);
		int width = strtol(line.c_str(), NULL, 10);
		engine->setScreenWidth(width);
		engine->setScreenScale(width / (float)DEFAULT_WIDTH);	// Scale of screen

		getline(config, line);
		engine->setScreenHeight(strtol(line.c_str(), NULL, 10));

		config.close();
	}
	else {
		return false;
	}

    return true;
}

bool game_init(HWND) {
	gsm = new GameStateManager();
	gsm->setState(menuState);

    return true;
}

void game_update() {
	gsm->update();
}

void game_keyPress(int key) {
	gsm->keyPressed(key);
}

void game_keyRelease(int key) {
	gsm->keyReleased(key);
}

void game_render() {
	engine->ClearScene(D3DCOLOR_XRGB(0, 0, 0));
	gsm->draw();
}


void game_end() {
	gsm->release();
	delete gsm;
}



