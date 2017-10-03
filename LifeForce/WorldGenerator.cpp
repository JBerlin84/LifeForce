/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-23
Project: Generates a random world

desc:
Generates random world based on a simple cellular autmata algorithm
************************************************************************/

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int xSize, int ySize, int fillRate,
	bool fillTop, bool fillBottom, bool fillLeft, bool fillRight) {
	this->xSize = xSize;
	this->ySize = ySize;
	this->fillRate = fillRate;

	this->fillBottom = fillBottom;
	this->fillLeft = fillLeft;
	this->fillRight = fillRight;
	this->fillTop = fillTop;

	vector<vector<int>> temp(xSize);
	world = temp;

	setSmoothProperties();
}

void WorldGenerator::setSmoothProperties(int smoothIterations, int smoothStrength) {
	this->smoothIterations = smoothIterations;
	this->smoothStrength = smoothStrength;
}

void WorldGenerator::setMinimumRegionSize(int minSize) {
	minRegionSize = minSize;
}

void WorldGenerator::fillWorld() {
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			int v;
			if (x == 0 && fillLeft)
				v = 1;
			else if (x == xSize - 1 && fillRight)
				v = 1;
			else if (y == 0 && fillTop)
				v = 1;
			else if (y == ySize - 1 && fillBottom)
				v = 1;
			else {
				int rand = std::rand() % 100;
				v = rand<fillRate ? 1 : 0;
			}
			world[x].push_back(v);
		}
	}
}

// iterates over the world to create something worth wile from the random
// matrix.
void WorldGenerator::smoothWorld() {
	vector<vector<int>> temp(xSize);
	
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			int neighbours = countNeighbours(x, y);
			
			if (neighbours > smoothStrength)
				temp[x].push_back(1);
			else if (neighbours < smoothStrength)
				temp[x].push_back(0);
			else
				temp[x].push_back(world[x][y]);
		}
	}

	world = temp;
}

// How many neighbours does given cell have.
int WorldGenerator::countNeighbours(int xPos, int yPos){
	int count = 0;
	for (int x = xPos - 1; x <= xPos + 1; x++) {
		for (int y = yPos-1; y <= yPos+1; y++) {
			if (x < 0)
				count += fillLeft ? 1 : 0;
			else if (x >= xSize)
				count += fillRight ? 1 : 0;
			else if (y < 0)
				count += fillTop ? 1 : 0;
			else if (y >= ySize)
				count += fillBottom ? 1 : 0;
			else
				count += world[x][y];
		}
	}
	return count;
}

vector<vector<int>> WorldGenerator::generateWorld() {
	fillWorld();

	for (int i = 0; i < smoothIterations; i++) {
		smoothWorld();
	}

	return world;
}

