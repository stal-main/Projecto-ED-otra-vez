#pragma once

//Clase grafo
// wiwiwiwiwiwiwiwiwi
//Hecha por Kevin Solano

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Pair.h"
#include "LinkedStack.h"

using std::cout;
using std::endl;

class Graph {

	Graph(const Graph&) = delete;

	void operator=(const Graph&) = delete;

private:

	int numNodes;

	int maxNeighbors;

	float* x;

	float* y;

	int** neighbors;

	float** weights;

	int* degree;

public:

	Graph(int numNodes, int maxNeighbors) {

		this->numNodes = numNodes;

		this->maxNeighbors = maxNeighbors;

		x = new float[numNodes]();

		y = new float[numNodes]();

		degree = new int[numNodes]();

		neighbors = new int*[numNodes];

		weights = new float*[maxNeighbors]();
	
	}

	~Graph() {

		for (int i = 0; i < numNodes; i++) {

			delete[] neighbors[i];

			delete[] weights[i];
		}

		delete[] neighbors;

		delete[] weights;

		delete[] x;

		delete[] y;

		delete[] degree;
	}
	

};

