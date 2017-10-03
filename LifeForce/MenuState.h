/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
A game state
Menu state manages the main menu and the options menu
************************************************************************/

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "GameState.h"
#include "GameStateEnum.h"
#include "Player.h"

enum whichMenuState { main, options };

class MenuState : public GameState {
public:
	MenuState(Player *player1, Player *player2, bool *twoPlayers);
	bool init(int width, int height);
	void draw();
	void update();
	void keyPressed(int k);
	void keyReleased(int k);
	void release();
private:
	void drawMainMenu();
	void drawOptionsMenu();
	void updateMainMenu();
	void updateOptionsMenu();
	void saveConfig();
	int  fetchCurrentSavestate();

	int currentMenuChoice;
	whichMenuState currentMenuState;
	int optionsCurrentResolution;
	int optionsIsFullscreen;
	bool isButtonRepeat;
	bool isButtonRepeatAction;
	CSound *music;
	bool startMusic;

	bool *twoPlayers;
	Player* player1;
	Player* player2;
};

#endif