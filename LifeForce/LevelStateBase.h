/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Base game state. Most levels use this gamestate. Special levels inherits
this class.
************************************************************************/

#ifndef LEVELSTATEBASE_H_
#define LEVELSTATEBASE_H_

#define PI 3.14159265358979323846

#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

#include "Player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "GameStateEnum.h"
#include "GameState.h"
#include "WorldGenerator.h"

class LevelStateBase : public GameState {
public:
	LevelStateBase(Player *player1, Player *player2, bool *twoPlayer, state thisGameState);
	bool init(int width = 1920, int height = 1080);
	void draw();
	void keyPressed(int k);
	void keyReleased(int k);
	void update();
	void release();

protected:
	void initWorld(char* filepath);
	void drawTilemap();
	void drawHUD();
	void checkCollisions();
	int isColliding(GameObject *a, GameObject *b);
	void createPlayerExplosion(Player* player);
	void createProjectileExplosion(GameObject* projectile);
	void spawnMissile(Player* player);
	void updateWorldXCoordinatesToCalculate();
	void checkVictoryCondition();
	void checkGameOverCondition();
	state thisGameState;
	Player* player1;
	Player* player2;
	Texture* explosion;
	bool* twoPlayers;
	void saveCheckpoint();
	CSound *music;

	double worldPosition;
	double worldSpeed;
	double backgroundParallax;
	double worldStartPosition;
	double worldEndPosition;
	int minimumWorldXCoordinate;				// make sure we dont calculate anything below this x coord in the world
	int maximumWorldXCoordinate;				// make sure we dont caluclate anything above this x coord in the world
	std::vector<std::vector<int>> world;
	std::vector<GameObject*> immutableObjects;
	std::vector<GameObject*> projectiles;
	std::vector<Enemy*> enemies;

private:
	bool player1ExplosionPlayed;				// Fulhack
};

#endif