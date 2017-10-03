/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Base game state. Most levels use this gamestate. Special levels inherits
this class.
************************************************************************/

#include "LevelStateBase.h"

LevelStateBase::LevelStateBase(Player *player1, Player *player2, bool *twoPlayers, state thisGameState) {
	this->thisGameState = thisGameState;
	this->player1 = player1;
	this->player2 = player2;
	player2->setPlayer2();

	this->twoPlayers = twoPlayers;

	player1ExplosionPlayed = false;
}

bool LevelStateBase::init(int width, int height) {

	char resourceFolder[100];
	char resourceResultString[100];
	char level[2];
	level[0] = (char)((int)thisGameState + 48);
	level[1] = (char)('\0');

	//resourceString
	strcpy_s(resourceFolder, "Resources\\Levels\\Level");
	strcat_s(resourceFolder, level);
	strcat_s(resourceFolder, "\\");

	background = new GameObject();
	strcpy_s(resourceResultString, resourceFolder);
	strcat_s(resourceResultString, "Background.png");
	if (!background->loadImage(resourceResultString)) {
		engine->message("Error loading background");
	}

	worldSprite = new GameObject();
	strcpy_s(resourceResultString, resourceFolder);
	strcat_s(resourceResultString, "Environment.png");
	if (!worldSprite->loadImage(resourceResultString)) {
		engine->message("Error loading sprite sheet for the environment");
	}
	worldSprite->setScale(0.5f);

	// init music
	strcpy_s(resourceResultString, resourceFolder);
	strcat_s(resourceResultString, "Music.wav");
	music = engine->LoadSound(resourceResultString);
	engine->LoopSound(music);

	// TODO: move this to another place.
	explosion = new Texture();
	if (!explosion->Load("Resources\\explosion.png")) {
		engine->message("Error loading sprite sheet for explosion");
	}

	int xPos = 0;
	int yPos = 0;
	background->setPosition(xPos, yPos);
	worldPosition = 0;
	worldSpeed = -2.5;
	backgroundParallax = 0.3;

	background->setScale(3.3);
	background->setVelocity(worldSpeed * backgroundParallax, 0);

	strcpy_s(resourceResultString, resourceFolder);
	strcat_s(resourceResultString, "Level.cfg");
	initWorld(resourceResultString);

	if (!*twoPlayers) {
		player2->setAlive(false);
	}
	player1->resetPosition();
	player2->resetPosition();

	saveCheckpoint();

	gameStateChanged = false;

	return true;
}

void LevelStateBase::initWorld(char* filepath) {
	std::string line;
	std::ifstream setup(filepath);

	if (setup.is_open()) {
		// Set world params
		getline(setup, line);
		worldStartPosition = std::stod(line);	// store world start position
		getline(setup, line);
		worldEndPosition = std::stod(line);		// store world end position

		// Create world
		getline(setup, line);
		int xSize = std::stoi(line);		// store world x size
		getline(setup, line);
		int ySize = std::stoi(line);		// store world y size
		getline(setup, line);
		int fillRate = std::stoi(line);		// store world fill rate
		WorldGenerator generator(xSize, ySize, fillRate);
		world = generator.generateWorld();

		// Create enemy force
		while (getline(setup, line)) {
			std::istringstream iss(line);
			vector<std::string> tokens{ std::istream_iterator < std::string > {iss}, std::istream_iterator < std::string > {} };
			if (tokens[0] == "1") {
				enemies.push_back(new Enemy01("Resources\\Enemy01.png", std::stoi(tokens[1]), std::stoi(tokens[2])));
			}
			else if (tokens[0] == "2") {
				enemies.push_back(new Enemy02("Resources\\Enemy02.png", std::stoi(tokens[1]), std::stoi(tokens[2])));
			}
		}

		setup.close();
	}
}

// Fulhack used to scale and draw gameobject at correct possition and sclae
void DrawGameObject(GameObject *o) {
	Vector3 pos = o->getPosition();
	double scale = o->getScale();
	
	o->setPosition(pos.getX()*engine->getScreenScale(), pos.getY()*engine->getScreenScale());
	o->setScale(scale*engine->getScreenScale());
	o->draw();

	o->setPosition(pos);
	o->setScale(scale);
}
// Fulhack used to scale and draw player at correct possition and scale
void DrawPlayerObject(Player *o) {
	Vector3 pos = o->getPosition();
	double scale = o->getScale();

	o->setPosition(pos.getX()*engine->getScreenScale(), pos.getY()*engine->getScreenScale());
	o->setScale(scale*engine->getScreenScale());
	o->draw();

	o->setPosition(pos);
	o->setScale(scale);
}

void LevelStateBase::draw() {
	DrawGameObject(background);
	if (player1->getAlive())
		DrawPlayerObject(player1);
	if (player2->getAlive())
		DrawPlayerObject(player2);

	drawTilemap();

	for (unsigned int i = 0; i < immutableObjects.size(); i++) {
		DrawGameObject(immutableObjects[i]);
	}
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		DrawGameObject(projectiles[i]);
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		DrawGameObject(enemies[i]);
	}

	drawHUD();
}

void LevelStateBase::keyPressed(int k) {
	if (player1->getAlive()) {
		if (k == DIK_UPARROW) {
			player1->goUp(true);
		}
		if (k == DIK_DOWNARROW) {
			player1->goDown(true);
		}
		if (k == DIK_LEFTARROW) {
			player1->goLeft(true);
		}
		if (k == DIK_RIGHTARROW) {
			player1->goRight(true);
		}
		if (k == DIK_RCONTROL) {
			spawnMissile(player1);
		}
	}

	if (player2->getAlive()) {
		if (k == DIK_W) {
			player2->goUp(true);
		}
		if (k == DIK_S) {
			player2->goDown(true);
		}
		if (k == DIK_A) {
			player2->goLeft(true);
		}
		if (k == DIK_D) {
			player2->goRight(true);
		}
		if (k == DIK_LCONTROL) {
			spawnMissile(player2);
		}
	}

	if (k == DIK_ESCAPE) {
		setNewGameState(menuState);
	}
}

void LevelStateBase::keyReleased(int k) {
	if (player1->getAlive()) {
		if (k == DIK_UPARROW) {
			player1->goUp(false);
		}
		if (k == DIK_DOWNARROW) {
			player1->goDown(false);
		}
		if (k == DIK_LEFTARROW) {
			player1->goLeft(false);
		}
		if (k == DIK_RIGHTARROW) {
			player1->goRight(false);
		}
	}

	if (player2->getAlive()) {
		if (k == DIK_W) {
			player2->goUp(false);
		}
		if (k == DIK_S) {
			player2->goDown(false);
		}
		if (k == DIK_A) {
			player2->goLeft(false);
		}
		if (k == DIK_D) {
			player2->goRight(false);
		}
	}
}

void LevelStateBase::update() {
	worldPosition += worldSpeed;
	updateWorldXCoordinatesToCalculate();
	checkVictoryCondition();
	checkGameOverCondition();

	for (unsigned int i = 0; i < immutableObjects.size(); i++) {
		immutableObjects[i]->animate();
		immutableObjects[i]->move();
		if (!immutableObjects[i]->getAlive()) {
			immutableObjects.erase(immutableObjects.begin() + i);
		}
	}

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->animate();
		projectiles[i]->move();
		if (projectiles[i]->getX() > 2500) {
			projectiles[i]->setAlive(false);
		}
		if (!projectiles[i]->getAlive()) {
			createProjectileExplosion(projectiles[i]);
			
			// Play missile sound
			if (projectiles[i]->getX() < 1920) {
				if (!player1ExplosionPlayed) {
					engine->playSound(player1->getMissileExplosionSound());
					player1ExplosionPlayed = true;
				}
				else {
					engine->playSound(player2->getMissileExplosionSound());
					player1ExplosionPlayed = false;
				}
			}
			projectiles.erase(projectiles.begin() + i);
		}
	}

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->animate();
		enemies[i]->update();
		if (!enemies[i]->getAlive()) {
			enemies.erase(enemies.begin() + i);
		}
	}

	background->move();
	if (player1->getAlive())
		player1->update();
	if (player2->getAlive())
		player2->update();

	checkCollisions();
}

void LevelStateBase::updateWorldXCoordinatesToCalculate() {
	minimumWorldXCoordinate = (int)((std::abs(worldPosition) - worldStartPosition) / (worldSprite->getWidth() * worldSprite->getScale()));
	if (minimumWorldXCoordinate < 0) {
		minimumWorldXCoordinate = 0;
	}

	maximumWorldXCoordinate = (int)(minimumWorldXCoordinate + (1920 / (worldSprite->getWidth() * worldSprite->getScale())) + 2);
	if (maximumWorldXCoordinate > (int)world.size()) {
		maximumWorldXCoordinate = (int)world.size();
	}
}

void LevelStateBase::checkVictoryCondition() {
	if (worldPosition <= worldEndPosition) {
		// Player has arrived to victory
		setNewGameState((state)(thisGameState + 1));
	}
}

void LevelStateBase::checkGameOverCondition() {
	if (!player1->getAlive() && !player2->getAlive()) {
		setNewGameState(defeatState);
	}
}

void LevelStateBase::saveCheckpoint() {
	std::ofstream state("Resources\\Savestate.dat");
	if (state.is_open()) {
		state << (int)thisGameState << std::endl;
		state << (*twoPlayers ? "1" : "0") << std::endl;
		state.close();
	}
}

void LevelStateBase::release() {
	// empty world
	for (int x = 0; x < (int)world.size(); x++) {
		for (int y = 0; y < (int)world[x].size(); y++) {
			world[x][y] = 0;
		}
	}

	immutableObjects.clear();
	projectiles.clear();
	enemies.clear();

	music->Stop();
	delete music;
	delete background;
}

void LevelStateBase::drawTilemap() {
	for (int x = minimumWorldXCoordinate; x < maximumWorldXCoordinate; x++) {
		for (int y = 0; y < (int)world[x].size(); y++) {
			if (world[x][y]) {
				int xPos = (int)(x*worldSprite->getWidth()*worldSprite->getScale() + worldPosition + worldStartPosition);
				int yPos = (int)(y*worldSprite->getHeight()*worldSprite->getScale());
				if (xPos > -worldSprite->getWidth() && xPos < 1920) {
					worldSprite->setPosition(xPos, yPos);
					DrawGameObject(worldSprite);
				}
			}
		}
	}
}

void LevelStateBase::drawHUD() {
	font->setScale(1 * engine->getScreenScale());

	if (player1->getHp() > 0) {
		font->Print((int)(10 * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "PLAYER1", 0xFF8888FF);
		for (int i = 0; i < player1->getHp()*3; i++) {
			font->Print((int)((350 + (i * 9)) * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "I", 0xFF8888FF);
		}
	}
	else {
		font->Print((int)(350 * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "DEAD", 0xFF8888FF);
	}

	if (*twoPlayers) {
		font->Print((int)(1380 * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "PLAYER2", 0xFFFF8888);
		if (player2->getHp() > 0) {
			for (int i = 0; i < player2->getHp() * 3; i++) {
				font->Print((int)((1720 + (i * 9)) * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "I", 0xFFFF8888);
			}
		}
		else {
			font->Print((int)(1720 * engine->getScreenScale()), (int)(10 * engine->getScreenScale()), "DEAD", 0xFFFF8888);
		}
	}
}

void LevelStateBase::checkCollisions() {
	// Check collision with world
	// As the world is a special case, this has to be done "right".
	for (int x = minimumWorldXCoordinate; x < maximumWorldXCoordinate; x++) {
		for (int y = 0; y < (int)world[x].size(); y++) {
			if (world[x][y]) {
				GameObject groundPiece;
				groundPiece.setSize((int)(worldSprite->getWidth()*worldSprite->getScale()), (int)(worldSprite->getHeight()*worldSprite->getScale()));
				groundPiece.setPosition(x*worldSprite->getWidth()*worldSprite->getScale() + worldPosition + worldStartPosition, y*worldSprite->getHeight()*worldSprite->getScale());

				// Check collision with player
				if (player1->getAlive() && isColliding(&groundPiece, player1)) {
					if (player1->hit()) {
						createPlayerExplosion(player1);
						player1->resetPosition();
					}
				}
				if (player2->getAlive() && isColliding(&groundPiece, player2)) {
					if (player2->hit()) {
						createPlayerExplosion(player2);
						player2->resetPosition();
					}
				}

				// Check collision with projectiles
				for (unsigned int i = 0; i < projectiles.size(); i++) {
					if (isColliding(&groundPiece, projectiles[i])) {
						projectiles[i]->setAlive(false);
						world[x][y] = 0;
					}
				}
			}
		}
	}

	// Check collision between projectiles and enemy
	for (unsigned int i = 0; i < enemies.size(); i++) {
		for (unsigned int j = 0; j < projectiles.size(); j++) {
			if (isColliding(enemies[i], projectiles[j])) {
				enemies[i]->hit();
				projectiles[j]->setAlive(false);
			}
		}

		if (player1->getAlive() && isColliding(enemies[i], player1)) {
			if (player1->hit()) {
				enemies[i]->hit();
				createPlayerExplosion(player1);
				player1->resetPosition();
			}
		}
		if (player2->getAlive() && isColliding(enemies[i], player2)) {
			if (player2->hit()) {
				enemies[i]->hit();
				createPlayerExplosion(player2);
				player2->resetPosition();
			}
		}
	}
}

void LevelStateBase::createProjectileExplosion(GameObject* projectile) {
	GameObject *o = new GameObject();
	o->setImage(explosion);
	o->setColumns(12);
	o->setTotalFrames(89);
	o->setSize(160, 120);
	o->setScale(2);
	o->setVelocity(worldSpeed, 0);
	o->repeatAnimation(false);

	int xPos = int(projectile->getPosition().getX() + 0.5f *projectile->getWidth()*projectile->getScale() - 0.5f * o->getWidth()*o->getScale());
	int yPos = int(projectile->getPosition().getY() + 0.5f *projectile->getHeight()*projectile->getScale() - 0.5f * o->getHeight()*o->getScale());
	o->setPosition(xPos, yPos);

	o->setCurrentFrame(0);
	immutableObjects.push_back(o);
}

void LevelStateBase::createPlayerExplosion(Player* player) {
	GameObject *o = new GameObject();
	o->setImage(player1->getExplosion());
	o->setColumns(12);
	o->setTotalFrames(89);
	o->setSize(160, 120);
	o->setScale(2);
	o->setVelocity(worldSpeed, 0);
	o->repeatAnimation(false);

	int xPos = int(player->getPosition().getX() + 0.5f *player->getWidth()*player->getScale() - 0.5f * o->getWidth()*o->getScale());
	int yPos = int(player->getPosition().getY() + 0.5f *player->getHeight()*player->getScale() - 0.5f * o->getHeight()*o->getScale());
	o->setPosition(xPos, yPos);

	o->setCurrentFrame(0);
	immutableObjects.push_back(o);

	o = new GameObject();
	o->setImage(player1->getPlayerDebris());
	o->setColumns(15);
	o->setTotalFrames(74);
	o->setSize(500, 500);
	o->setScale(1.0f);
	o->setVelocity(worldSpeed, 0);
	o->repeatAnimation(false);

	xPos = int(player->getPosition().getX() + 0.5f *player->getWidth()*player->getScale() - 0.5f * o->getWidth()*o->getScale());
	yPos = int(player->getPosition().getY() + 0.5f *player->getHeight()*player->getScale() - 0.5f * o->getHeight()*o->getScale());
	o->setPosition(xPos, yPos);

	o->setCurrentFrame(0);
	immutableObjects.push_back(o);
}

void LevelStateBase::spawnMissile(Player* player) {
	if (player->getFireTimer()->stopwatch(player->getRateOfFire())) {
		GameObject* o = new GameObject();
		o->setImage(player->getMissile());
		o->setVelocity(player->getMissileSpeed(), 0);
		o->setScale(0.5);
		o->setRotation(0.5*PI);

		int xPos = int(player->getPosition().getX() + player->getWidth()*player->getScale());
		int yPos = int(player->getPosition().getY() + 0.5f *player->getHeight()*player->getScale() +10 - 0.5f * o->getHeight()*o->getScale());
		o->setPosition(xPos, yPos);

		projectiles.push_back(o);
		engine->playSound(player->getMissileSound());
		player->getFireTimer()->reset();
	}
}

int LevelStateBase::isColliding(GameObject *a, GameObject *b) {
	RECT r1;
	r1.top = (long)a->getPosition().getY();
	r1.bottom = (long)(a->getPosition().getY() + a->getHeight() * a->getScale());
	r1.left = (long)a->getPosition().getX();
	r1.right = (long)(a->getPosition().getX() + a->getWidth() * a->getScale());

	RECT r2;
	r2.top = (long)b->getPosition().getY();
	r2.bottom = (long)(b->getPosition().getY() + b->getHeight() * b->getScale());
	r2.left = (long)b->getPosition().getX();
	r2.right = (long)(b->getPosition().getX() + b->getWidth() * b->getScale());

	RECT dest;
	return IntersectRect(&dest, &r1, &r2);
}