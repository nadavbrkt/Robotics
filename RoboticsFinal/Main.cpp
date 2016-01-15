/*
 * Main.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#include "Map.h"
#include "STC.h"

using namespace std;

int main() {
	Map map(0.02,0.45);

	map.loadMap("roboticLabMap.png");
	map.convertImageToGrid();
	//map.print();
	map.inflateObstacles();
	map.buildFineGrid();
	map.buildCoarseGrid();
	//map.saveMapToImage("LabInflateObsticale.png");
	//map.saveFineGridToImage("LabFineGrid.png");
	//map.saveCoarseGridToImage("LabCoarseGrid.png");
	map.printCoarseGrid();
	cout << endl << "ok1 " << endl;

	STC stc(map, Position(6,8));
	stc.buildSpanningTree();



	return 0;
}

