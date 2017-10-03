/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-08-23
Project: Introduction to game programming in windows, project assignment

desc:
Holds the enemy in the game
************************************************************************/

#include "Enemy.h"

Enemy::Enemy(std::string filename, int startPosX, int startPosY, bool hasPowerUp, D3DCOLOR transcolor) : GameObject() {

	if (!loadImage(filename, transcolor)) {
		engine->message("Error loading enemy sprite!");
	}

	int xPos = startPosX;
	int yPos = startPosY;
	setPosition(xPos, yPos);
	setScale(1);
	setColumns(12);
	setTotalFrames(81);
	setSize(76, 76);
	setCurrentFrame(1);

	points = 0;
	this->hasPowerUp = hasPowerUp;
}

void Enemy::draw() {
	GameObject::draw();
}

void Enemy::update() {
	setX(getX() - 10);
}

int Enemy::getPoints() {
	return points;
}

void Enemy::hit() {
	setAlive(false);
}

Texture* Enemy::getEnemyDebris() {
	return enemyDebris;
}
Texture* Enemy::getExplosion() {
	return explosion;
}