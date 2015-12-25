/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
using namespace std;

typedef vector<vector<bool> > Grid;

class Map {
private:
	vector<unsigned char> image;
	Grid map;
	unsigned int mapWidth;
	unsigned int mapHeight;

	float mapResolution;
	float robotSize;
	int robotSizeInCells;
	int inflationRadius;

	Grid fineGrid; // each cell in the size of the robot
	Grid coarseGrid; // each cell in the size 2x2 of the fine grid cell

	bool checkIfCellIsOccupied(int i, int j);
	void printGrid(const Grid &grid) const;
	void inflateObstacles() const;

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath);
	void saveMapToFile(const char* filePath);
	void buildFineGrid();
	void buildCoarseGrid();

	virtual ~Map();
};

#endif /* MAP_H_ */
