/*
 * Map.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(float mapResolution, float robotSize) {
	this->mapResolution = mapResolution;
	this->robotSize = robotSize;
	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = robotSizeInCells * 0.3;
	cout << "inflationRadius: " << inflationRadius << endl;

}

void Map::loadMap(const char* filePath)
{
	lodepng::decode(image, mapWidth, mapHeight, filePath);
	cout << "map width: " << mapWidth << "\t map height:" << mapHeight << endl;

}

void Map::convertImageToGrid()
{
	// Realloc 2D array
	map.resize(mapHeight);
	for (int i=0; i < mapHeight; ++i)
		map[i].resize(mapWidth);

	//
	int imageCounter = 0;
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			if (this->image[imageCounter] == NOT_IMAGE_OBSTACLE)
				map[i][j] = NOT_OBSTACLE;
			else
				map[i][j] = OBSTACLE;
			imageCounter += 4;
		}
	}
}

void Map::inflateObstacles()
{
	Grid tempMap;

	// Realloc 2D temp array
	tempMap.resize(mapHeight);
	for (int i=0; i < mapHeight; ++i)
		tempMap[i].resize(mapWidth,0);

	// Build map with inflate obstacles
	for (int i = 0 ; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			if (map[i][j] == true)
			{
				inflateCell(tempMap,i,j);
			}
		}
	}

	// copy tempMap to Map
	for (int i = 0 ; i < mapHeight; ++i)
	{
			for (int j = 0; j <mapWidth; ++j)
			{
				map[i][j] = tempMap[i][j];
			}
	}
}

void Map::printMap()
{
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Map::printCoarseGrid()
{
	for (int i = 0; i < mapHeight/robotSizeInCells/2; ++i)
	{
		for (int j = 0; j < mapWidth/robotSizeInCells/2; ++j)
		{
			cout << coarseGrid[i][j] << " ";
		}
		cout << endl;
	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::inflateCell(vector<vector<bool> > &tempMap, int i, int j)
{
	for (int a = i-inflationRadius; a< i+inflationRadius; ++a)
	{
		for (int b = j- inflationRadius; b < j + inflationRadius; ++b)
		{
			if ((a >= 0) && (b >= 0) && (a < mapHeight) && (b < mapWidth))
			{
				tempMap[a][b] = OBSTACLE;
			}
		}
	}
}

void Map::saveMapToImage(const char* filePath)
{
	vector<unsigned char> temp;
	temp.resize(mapHeight*mapWidth*4);
	int imageCounter = 0;
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			if (map[i][j] == OBSTACLE)
			{
				temp[imageCounter] = IMAGE_OBSTACLE;
				temp[imageCounter+1] = IMAGE_OBSTACLE;
				temp[imageCounter+2] = IMAGE_OBSTACLE;
				temp[imageCounter+3] = 255;
			}
			else
			{
				temp[imageCounter] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+1] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+2] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+3] = NOT_IMAGE_OBSTACLE;
			}
			imageCounter += 4;
		}
	}

	lodepng::encode(filePath, temp, mapWidth, mapHeight);
}

void Map::saveFineGridToImage(const char* filePath)
{
	int fineMapHeight = mapHeight/robotSizeInCells;
	int fineMapWidth = mapWidth/robotSizeInCells;
	vector<unsigned char> temp;

	temp.resize(fineMapHeight*fineMapWidth*4);
	int imageCounter = 0;
	for (int i = 0; i < fineMapHeight; ++i)
	{
		for (int j = 0; j < fineMapWidth; ++j)
		{
			if (fineGrid[i][j] == OBSTACLE)
			{
				temp[imageCounter] = IMAGE_OBSTACLE;
				temp[imageCounter+1] = IMAGE_OBSTACLE;
				temp[imageCounter+2] = IMAGE_OBSTACLE;
				temp[imageCounter+3] = 255;
			} 			else
			{
				temp[imageCounter] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+1] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+2] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+3] = NOT_IMAGE_OBSTACLE;
			}
			imageCounter += 4;
		}
	}

	lodepng::encode(filePath, temp, fineMapWidth, fineMapHeight);
}

void Map::saveCoarseGridToImage(const char* filePath)
{
	int coarseMapHeight = mapHeight/robotSizeInCells/2;
	int coarseMapWidth = mapWidth/robotSizeInCells/2;
	vector<unsigned char> temp;

	temp.resize(coarseMapHeight*coarseMapWidth*4);
	int imageCounter = 0;
	for (int i = 0; i < coarseMapHeight; ++i)
	{
		for (int j = 0; j < coarseMapWidth; ++j)
		{
			if (coarseGrid[i][j] == OBSTACLE)
			{
				temp[imageCounter] = IMAGE_OBSTACLE;
				temp[imageCounter+1] = IMAGE_OBSTACLE;
				temp[imageCounter+2] = IMAGE_OBSTACLE;
				temp[imageCounter+3] = 255;
			}
			else
			{
				temp[imageCounter] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+1] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+2] = NOT_IMAGE_OBSTACLE;
				temp[imageCounter+3] = NOT_IMAGE_OBSTACLE;
			}
			imageCounter += 4;
		}
	}

	lodepng::encode(filePath, temp, coarseMapWidth, coarseMapHeight);
}

void Map::buildFineGrid()
{
	int fineMapHeight = mapHeight/robotSizeInCells;
	int fineMapWidth = mapWidth/robotSizeInCells;

	// Realloc 2D array
	fineGrid.resize(fineMapHeight);
	for (int i=0; i < (fineMapHeight); ++i)
			fineGrid[i].resize(fineMapWidth);


	// For cell in fineGrid
	for (int fineI = 0; fineI < fineMapHeight; ++fineI)
	{
		for (int fineJ = 0; fineJ < fineMapWidth; ++fineJ)
		{

			// For every cell
			bool flag = true;
			int i = (fineI*robotSizeInCells);

			while (((i < ((fineI+1)*robotSizeInCells)) && (flag)))
			{
				int j = (fineJ*robotSizeInCells);
				while (j <((fineJ+1)*robotSizeInCells))
				{
					if (map[i][j] == OBSTACLE)
					{
						fineGrid[fineI][fineJ] = OBSTACLE;
						flag = false;
					}
					++j;
				}
				++i;
			}

			if (flag)
				fineGrid[fineI][fineJ] = NOT_OBSTACLE;
		}
	}
}

void Map::buildCoarseGrid()
{
	int coarseMapHeight = mapHeight/robotSizeInCells/2;
	int coarseMapWidth = mapWidth/robotSizeInCells/2;

	// Realloc 2D array
	coarseGrid.resize(coarseMapHeight);
	for (int i=0; i < (coarseMapHeight); ++i)
		coarseGrid[i].resize(coarseMapWidth);

	// For cell in coarseGrid
	for (int coarseI = 0; coarseI < coarseMapHeight; ++coarseI)
	{
		for (int coarseJ = 0; coarseJ < coarseMapWidth; ++coarseJ)
		{

			// For every cell
			bool flag = true;
			int i = (coarseI*2);

			while (((i < ((coarseI+1)*2)) && (flag)))
			{
				int j = (coarseJ*2);
				while (j <((coarseJ+1)*2))
				{
					if (fineGrid[i][j] == OBSTACLE)
					{
						coarseGrid[coarseI][coarseJ] = OBSTACLE;
						flag = false;
					}
					++j;
				}
				++i;
			}
			if (flag)
			{
				coarseGrid[coarseI][coarseJ] = NOT_OBSTACLE;
			}
		}
	}
}

