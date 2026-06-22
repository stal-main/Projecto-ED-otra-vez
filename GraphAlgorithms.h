#pragma once

#include "Graph.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "MinHeap.h"
#include "Pair.h"

Graph* dfs(const Graph& g, int startNode) {

	int n = g.getNumNodes();

	Graph* tree = new Graph(n, g.getMaxNeighbors());

	for (int i = 0; i < n; i++) {

		tree->setPosition(i, g.getX(i), g.getY(i));
	}

	bool* visited = new bool[n]();

	LinkedStack<Pair<int, int>> stack;

	stack.push(Pair<int, int>(startNode, -1));

	while (!stack.isEmpty()) {

		Pair<int, int> current = stack.pop();

		int node = current.key;

		int parent = current.value;

		if (!visited[node]) {

			visited[node] = true;

			if (parent != -1) {

				float weight = g.findWeight(node, parent);

				tree->addEdge(node, parent, weight);
			}

			for (int i = 0; i < g.getDegree(node); i++) {

				int neighbor = g.getNeighbor(node, i);

				if (!visited[neighbor]) {

					stack.push(Pair<int, int>(neighbor, node));
				}
			}
		}
	}

	delete[] visited;

	return tree;
}

Graph* bfs(const Graph& g, int startNode) {

	int n = g.getNumNodes();

	Graph* tree = new Graph(n, g.getMaxNeighbors());

	for (int i = 0; i < n; i++) {

		tree->setPosition(i, g.getX(i), g.getY(i));
	}

	bool* visited = new bool[n]();

	LinkedQueue<Pair<int, int>> queue;

	queue.enqueue(Pair<int, int>(startNode, -1));

	while (!queue.isEmpty()) {

		Pair<int, int> current = queue.dequeue();

		int node = current.key;

		int parent = current.value;

		if (!visited[node]) {

			visited[node] = true;

			if (parent != -1) {

				float weight = g.findWeight(node, parent);

				tree->addEdge(node, parent, weight);
			}

			for (int i = 0; i < g.getDegree(node); i++) {

				int neighbor = g.getNeighbor(node, i);

				if (!visited[neighbor]) {

					queue.enqueue(Pair<int, int>(neighbor, node));
				}
			}
		}
	}

	delete[] visited;

	return tree;
}

Graph* prim(const Graph& g, int startNode) {

	int n = g.getNumNodes();

	Graph* tree = new Graph(n, g.getMaxNeighbors());

	for (int i = 0; i < n; i++) {

		tree->setPosition(i, g.getX(i), g.getY(i));
	}

	bool* inTree = new bool[n]();

	MinHeap<Pair<float, Pair<int, int>>> heap(n * g.getMaxNeighbors());

	inTree[startNode] = true;
	
	for (int i = 0; i < g.getDegree(startNode); i++) {

		int neighbor = g.getNeighbor(startNode, i);

		float weight = g.findWeight(startNode, neighbor);

		heap.insert(Pair<float, Pair<int, int>>(weight, Pair<int, int>(startNode, neighbor)));
	}

	while (heap.getSize() > 0) {

		Pair<float, Pair<int, int>> minEdge = heap.removeFirst();

		int node = minEdge.value.key;

		int parent = minEdge.value.value;

		float weight = minEdge.key;

		if (!inTree[node]) {

			inTree[node] = true;

			tree->addEdge(node, parent, weight);

			for (int i = 0; i < g.getDegree(node); i++) {

				int neighbor = g.getNeighbor(node, i);

				if (!inTree[neighbor]) {

					float weight = g.findWeight(node, neighbor);

					heap.insert(Pair<float, Pair<int, int>>(weight, Pair<int, int>(node, neighbor)));
				}
			}
		}
	}
	

	delete[] inTree;

	return tree;
}


