/*
 * Main.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#include "Map.h"

using namespace std;

void saveMapToImage();

int main() {
	Map map(0.02,0.45);

	map.loadMap("roboticLabMap.png");
	map.convertImageToGrid();
	//map.print();
	map.buildFineGrid();
	map.inflateObstacles();
	cout<< "ok0" <<endl;
	//map.print();
	map.convertGridToImage();
	cout<< "ok1" <<endl;
	map.saveMap("roboticLabMap2.png");
	map.saveGrid("roboticLabGrid.png");
	//map.print();


	return 0;
}


void saveMapToImage(const char* filePath, )
{
	lodepng::encode(filePath, inflateObstaclesImage, mapWidth, mapHeight);
}
