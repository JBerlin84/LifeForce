/************************************************************************
Author: Jimmy Berlin
Last modified: 2015-12-23
Project: Generates a random world

desc:
Generates random world based on a simple cellular autmata algorithm
************************************************************************/

#ifndef WORLD_GENERATOR_H_
#define WORLD_GENERATOR_H_

#include <vector>
#include <stdlib.h>

using std::vector;

class WorldGenerator {
public:
	WorldGenerator(int xSize, int ySize, int fillRate, bool fillTop = true, bool fillBottom = true, bool fillLeft = false, bool fillRight = false);
	void setSmoothProperties(int smoothIterations = 5, int smoothStrength = 4);
	void setMinimumRegionSize(int minSize = 6);
	vector<vector<int>> generateWorld();
private:
	void fillWorld();
	void smoothWorld();
	int countNeighbours(int xPos, int yPos);

	int xSize, ySize, fillRate;
	bool fillTop, fillBottom, fillLeft, fillRight;
	int smoothIterations, smoothStrength;
	int minRegionSize;

	vector<vector<int>> world;
};

#endif