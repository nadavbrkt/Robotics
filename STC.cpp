/*
 * STC.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "STC.h"

STC::STC(Map &map, Position initialRobotPos) : map(map), initialRobotPos(initialRobotPos) {
	// TODO Auto-generated constructor stub
	this->buildGraph();

	/* TODO: debug
	cout << "6,8: " << this->graph[6][8]->neighborsInTree.size() << endl;
	cout << "5,8: " << this->graph[5][8]->neighborsInTree.size() << endl;
	cout << "0,0: " << this->graph[0][0]->neighborsInTree.size() << endl;
	cout << "7,0: " << this->graph[7][0]->neighborsInTree.size() << endl;
	cout << "7,1: " << this->graph[7][1]->neighborsInTree.size() << endl;
	*/
}

STC::~STC() {
	// TODO Auto-generated destructor stub
}

void STC::DFS(Node *node) {
	// 1. Go over all the neighbors of the node in the graph
	// 2. For each neighbor, if not visited:
	// 	  2a. Add tree edge between node and neighbor
	//    2b. Recursively call DFS with neighbor

	cout << "row: " <<node->row << " " << "col: " << node->col << endl;
	node->visited = true;
	for (int i = 0; i < node->neighborsInTree.size(); ++i)
	{
		if (node->neighborsInTree[i]->visited == false)
		{
			this->DFS(node->neighborsInTree[i]);
		}
	}

}

void STC::buildGraph()
{
	graphHight = map.coarseGrid.size();
	graphWidth = map.coarseGrid[0].size();

	// // Realloc 2D graph and initialize it
	graph.resize(graphHight);
	for (int i=0; i < graphHight; ++i)
	{
		graph[i].resize(graphWidth);

		for (int j = 0;  j < graphWidth; ++j)
		{
			graph[i][j] = new Node(i,j);
		}
	}

	// Initialize nodes neighbors in tree
	for (int i = 0;  i < graphHight; ++i)
	{
		for (int j = 0;  j < graphWidth; ++j)
		{
			if (map.coarseGrid[i][j] == 0)
			{
				if ((i != 0) && (map.coarseGrid[i-1][j] == 0))
				{
					graph[i][j]->neighborsInTree.push_back(graph[i-1][j]);
				}

				if ((i != graphHight - 1) && (map.coarseGrid[i+1][j] == 0))
				{
					graph[i][j]->neighborsInTree.push_back(graph[i+1][j]);
				}

				if ((j != 0) && (map.coarseGrid[i][j-1] == 0))
				{
					graph[i][j]->neighborsInTree.push_back(graph[i][j-1]);
				}

				if ((j != graphWidth - 1) && (map.coarseGrid[i][j+1] == 0))
				{
					graph[i][j]->neighborsInTree.push_back(graph[i][j+1]);
				}
			}
		}
	}
}

void STC::buildSpanningTree()
{
	this->DFS(this->graph[0][0]);
}
