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

	//calcula la distancia entre dos nodos
	float distance(int i, int j) {

		float dx = x[i] - x[j];

		float dy = y[i] - y[j];

		return sqrtf(dx * dx + dy * dy);
	}

public:

	Graph(int numNodes, int maxNeighbors) {

		this->numNodes = numNodes;

		this->maxNeighbors = maxNeighbors;

		x = new float[numNodes]();

		y = new float[numNodes]();

		degree = new int[numNodes]();

		neighbors = new int*[numNodes];

		weights = new float*[maxNeighbors]();

		for (int i = 0; i < numNodes; i++) {

			neighbors[i] = new int[maxNeighbors]();

			weights[i] = new float[maxNeighbors]();
		}
	
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

	int getNumNodes() {

		return numNodes;
	}

	int getMaxNeighbors() {

		return maxNeighbors;
	}
	

};

