/*
 * STC.h
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#ifndef STC_H_
#define STC_H_

#include "Map.h"
#include "Node.h"
using namespace std;

typedef pair<int, int> Position;

class STC {
private:
	Map &map;
	vector<vector< Node *> > graph;
	Node *startNode;

	void buildGraph();
	void DFS(Node *node);

public:
	STC(Map &map, Position startPos);
	void buildSpanningTree();
	virtual ~STC();
};

#endif /* STC_H_ */
