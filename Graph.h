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

	float findWeight(int u, int v) {

		for (int i = 0; i < degree[u]; i++) {

			if (neighbors[u][i] == v) {

				return weights[u][i];
			}
		}

		return -1.0f;
	}

public:

	Graph(int numNodes, int maxNeighbors) {

		this->numNodes = numNodes;

		this->maxNeighbors = maxNeighbors;

		x = new float[numNodes]();

		y = new float[numNodes]();

		degree = new int[numNodes]();

		neighbors = new int*[numNodes];

		weights = new float*[numNodes];

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

	int getNumNodes() const {

		return numNodes;
	}

	int getMaxNeighbors() const {

		return maxNeighbors;
	}

	float getX(int i) const {

		return x[i];
	}

	float getY(int i) const {

		return y[i];
	}

	int getDegree(int i) const {

		return degree[i];
	}

	int getNeighbor(int i, int k) const {

		return neighbors[i][k];
	}

	int getWeight(int i, int k) const {

		return weights[i][k];
	}

	void setPosition(int i, float px, float py) {

		x[i] = px;
		y[i] = py;
	}

	bool addEdge(int u, int v, float weight) {
		
		if (degree[u] >= maxNeighbors || degree[v] >= maxNeighbors) {

			return false;
		}

		for (int i = 0; i < degree[u]; i++) {

			if (neighbors[u][i] == v) {

				return false;
			}
		}
		
		neighbors[u][degree[u]] = v;

		weights[u][degree[u]] = weight;

		degree[u]++;

		neighbors[v][degree[v]] = u;

		weights[v][degree[v]] = weight;

		degree[v]++;

		return true;
	}

	void generateRandom(float connectionDist, float width = 120.0f) {

		float margin = 40.0f;

		for (int i = 0; i < numNodes; i++) {

			degree[i] = 0;
		}

		for (int i = 0; i < numNodes; i++) {

			x[i] = margin + (float)rand() / RAND_MAX * (width - 2 * margin);

			y[i] = margin + (float)rand() / RAND_MAX * (width - 2 * margin);
		}

		for (int i = 0; i < numNodes; i++) {

			for (int j = i + 1; j < numNodes; j++) {

				float d = distance(i, j);

				if (d <= connectionDist) {

					addEdge(i, j, d);

				}
			}
		}
	}
};

