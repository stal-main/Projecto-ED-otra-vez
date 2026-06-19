

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Graph.h"
#include "GraphAlgorithms.h"

using std::cout;
using std::endl;

const int NUM_NODES = 20;

const int MAX_NEIGHBORS = 6;

const float CONNECTION_DIST = 200.0f;

int main() {

	srand((unsigned)time(nullptr));

	Graph g(NUM_NODES, MAX_NEIGHBORS);

	g.generateRandom(CONNECTION_DIST);

	cout << "Original graph:" << endl;

	g.print();

	cout << endl;

	int startNode = 0;

	Graph* tree = dfs(g, startNode);

	cout << "DFS tree starting from node " << startNode << ":" << endl;

	tree->print();

	delete tree;	

	return 0;
}

