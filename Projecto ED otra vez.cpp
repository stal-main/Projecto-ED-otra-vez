

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Graph.h"

using::cout;
using::endl;

const int NUM_NODES = 20;

const int MAX_NEIGHBORS = 6;

int main() {

	srand((unsigned)time(nullptr));

	Graph g(NUM_NODES, MAX_NEIGHBORS);



	return 0;
}

