/*
 * Map.h
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <iostream>
#include "lodepng.h"

#define OBSTACLE true
#define NOT_OBSTACLE false
#define IMAGE_OBSTACLE 0
#define NOT_IMAGE_OBSTACLE 255

using namespace std;

typedef vector<vector<bool> > Grid;

class Map {
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	float mapResolution;
	float robotSize;
	int robotSizeInCells;
	int inflationRadius;

	vector<unsigned char> image;
	vector<unsigned char> inflateObstaclesImage;
	Grid map;
	Grid fineGrid; // cell size equal to robot size
	Grid coarseGrid; // cell size is 4*robot size



	void buildCoarseGrid();

	void printGrid(const Grid &grid) const;			//
	void inflateCell(Grid &tempMap, int i, int j);	//

public:
	void buildFineGrid();
	Map(float mapResolution, float robotSize); 		//
	void loadMap(const char* filePath);				//
	void saveMap(const char* filePath);				//
	void convertImageToGrid();						//
	void convertGridToImage();						//
	void inflateObstacles();						//
	void print();									//
	virtual ~Map();									//
	void saveGrid(const char * filePath);

};

#endif /* MAP_H_ */
