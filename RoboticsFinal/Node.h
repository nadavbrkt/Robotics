/*
 * Node.h
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

class Node {
public:
	int row, col;
	bool visited;
	vector<Node *> neighborsInSpanningTree;

	Node(int row, int col);
	virtual ~Node();
};

#endif /* NODE_H_ */
