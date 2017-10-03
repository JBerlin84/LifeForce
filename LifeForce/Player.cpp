/************************************************************************
Author: Jimmy Berlin
Last modified: 2016-01-10
Project: Introduction to game programming in windows, project assignment

desc:
Holds the player in the game
************************************************************************/

#include "Player.h"

Player::Player(std::string filename, D3DCOLOR transcolor) : GameObject() {
	
	if (!loadImage(filename, transcolor)) {
		engine->message("Error loading player sprite!");
	}

	explosion = new Texture();
	explosion->Load("resources\\explosion.png");
	playerDebris = new Texture();
	playerDebris->Load("resources\\shipDebris.png");
	missile = new Texture();
	missile->Load("resources\\Missile.png");
	missileSound = engine->LoadSound("resources\\Missile.wav");
	missileExplosionSound = engine->LoadSound("resources\\Explosion.wav");

	int xPos = engine->getScreenWidth() / 2 - width / 2;
	int yPos = engine->getScreenHeight() / 2 - height / 2;
	setPosition(xPos, yPos);
	setScale(0.25);
	setColumns(1);
	setTotalFrames(3);
	setSize(633, 171);
	setCurrentFrame(1);

	player2 = false;
	up = down = left = right = false;

	fireTimer = new Timer();
	rateOfFire = 500;
	immortalTimer = new Timer();
	immortalTimer->reset();
	immortalTime = 2000;
	flickerTimer = new Timer();
	flickerSpeed = 70;
	immortal = false;
	points = 0;
	missileSpeed = 20;
	hp = maxHp = 3;
}

void Player::draw() {
	if (immortal) {
		if (flickerTimer->stopwatch(flickerSpeed)) {
			displayFlicker = !displayFlicker;
		}
		if (displayFlicker) {
			GameObject::draw();
		}
	}
	else {
		GameObject::draw();
	}
}

void Player::update() {
	if (getAlive()) {
		if (left) {
			setX(getX() - 5);
		}
		if (right) {
			setX(getX() + 5);
		}
		if (up) {
			setCurrentFrame(0);
			setY(getY() - 5);
		}
		if (down) {
			setCurrentFrame(2);
			setY(getY() + 5);
		}
		if (!(up || down)) {
			setCurrentFrame(1);
		}

		if (immortal) {
			if (immortalTimer->stopwatch(immortalTime)) {
				immortal = false;
			}
		}

		clampToScreen();
		if (hp <= 0) {
			setAlive(false);
		}
	}
}

void Player::setPlayer2() {
	player2 = true;
}

void Player::resetPosition() {
	if (!player2)
		setPosition(1920 / 4, 1080 / 3);
	else
		setPosition(1920 / 4, 1080 / 3 * 2);

	goUp(false);
	goDown(false);
	goLeft(false);
	goRight(false);
}

void Player::clampToScreen() {
	double x = getX();
	double y = getY();
	double width = this->width*scaling;
	double height = this->height*scaling;

	if (x < 0)
		x = 0;
	if (x > 1920 - width)
		x = 1920 - width;
	if (y < 0)
		y = 0;
	if (y > 1080 - height)
		y = 1080 - height;

	setPosition(x, y);
}

void Player::goLeft(bool v) {
	left = v;
}

void Player::goRight(bool v) {
	right = v;
}

void Player::goUp(bool v) {
	up = v;
}

void Player::goDown(bool v) {
	down = v;
}

void Player::setRateOfFire(int rate) {
	rateOfFire = rate;
}

int Player::getRateOfFire() {
	return rateOfFire;
}

void Player::addPoints(int pointsToAdd) {
	points += pointsToAdd;
}

int Player::getPoints() {
	return points;
}

Timer* Player::getFireTimer() {
	return fireTimer;
}

bool Player::hit() {
	bool hit = false;
	if (!immortal) {
		immortal = true;
		immortalTimer->reset();
		flickerTimer->reset();
		--hp;
		hit = true;
	}
	return hit;
}

bool Player::getImmortal() {
	return immortal;
}

int Player::getHp() {
	return hp;
}

void Player::setHp(int hp) {
	this->hp = hp;
}

int Player::getMaxHp() {
	return maxHp;
}

Texture* Player::getPlayerDebris() {
	return playerDebris;
}
Texture* Player::getExplosion() {
	return explosion;
}

Texture* Player::getMissile() {
	return missile;
}

float Player::getMissileSpeed() {
	return missileSpeed;
}

CSound* Player::getMissileSound() {
	return missileSound;
}

CSound* Player::getMissileExplosionSound() {
	return missileExplosionSound;
}