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

		heap.insert(Pair<float, Pair<int, int>>(weight, Pair<int, int>(neighbor, startNode)));
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

					float edgeWeight = g.findWeight(node, neighbor);

					heap.insert(Pair<float, Pair<int, int>>(edgeWeight, Pair<int, int>(neighbor, node)));
				}
			}
		}
	}
	

	delete[] inTree;

	return tree;
}

int kruskalFind(int* parent, int i) {
	while (parent[i] != i) {
		i = parent[i];
	}
	return i;
}

void kruskalUnite(int* parent, int src, int dst) {
	parent[kruskalFind(parent, src)] = kruskalFind(parent, dst);
}

Graph* kruskal(const Graph& g) {
	int n = g.getNumNodes();
	Graph* tree = new Graph(n, g.getMaxNeighbors());
	for (int i = 0; i < n; i++) {
		tree->setPosition(i, g.getX(i), g.getY(i));
	}
	int totalEdges = 0;
	for (int src = 0; src < n; src++) {
		for (int i = 0; i < g.getDegree(src); i++) {
			if (src < g.getNeighbor(src, i)) {
				totalEdges++;
			}
		}
	}

	if (totalEdges == 0) {
		return tree;
	}

	MinHeap<Pair<float, Pair<int, int>>> heap(totalEdges);
	for (int src = 0; src < n; src++) {
		for (int i = 0; i < g.getDegree(src); i++) {
			int dst = g.getNeighbor(src, i);
			if (src < dst) {
				float w = g.getWeight(src, i);
				heap.insert(Pair<float, Pair<int, int>>(w, Pair<int, int>(src, dst)));
			}
		}
	}
	int* parent = new int[n];

	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	while (heap.getSize() > 0) {
		Pair<float, Pair<int, int>> e = heap.removeFirst();
		int src = e.value.key;
		int dst = e.value.value;
		float w = e.key;
		if (kruskalFind(parent, src) != kruskalFind(parent, dst)) {
			tree->addEdge(src, dst, w); 
			kruskalUnite(parent, src, dst);
		}
	}

	delete[] parent;

	return tree;
}

Graph* dijkstra(const Graph& g, int source, int target) {
	int n = g.getNumNodes();
	float* dist = new float[n];
	int* prev = new int[n];
	bool* visited = new bool[n]();

	for (int i = 0; i < n; i++) {
		dist[i] = 2000;
		prev[i] = -1;
	}
	dist[source] = 0;
	MinHeap<Pair<float, int>> heap(n * g.getMaxNeighbors() + 1);
	heap.insert(Pair<float, int>(0, source));

	while (heap.getSize() > 0) {
		Pair<float, int> current = heap.removeFirst();
		int src = current.value;
		float distSrc = current.key;
		if (visited[src]) {
			continue;
		}
		visited[src] = true;
		if (src == target) {
			break;
		}
		for (int i = 0; i < g.getDegree(src); i++) {
			int dst = g.getNeighbor(src, i);
			float w = g.getWeight(src, i);
			if (!visited[dst] && distSrc + w < dist[dst]) {
				dist[dst] = distSrc + w;
				prev[dst] = src;
				heap.insert(Pair<float, int>(dist[dst], dst));
			}
		}
	}
	if (prev[target] == -1 && target != source) {
		delete[] dist;
		delete[] prev;
		delete[] visited;
		return nullptr;
	}
	Graph* result = new Graph(n, g.getMaxNeighbors());
	for (int i = 0; i < n; i++) {
		result->setPosition(i, g.getX(i), g.getY(i));
	}
	int cur = target;
	while (prev[cur] != -1) {
		int p = prev[cur];
		float w = dist[cur] - dist[p];
		result->addEdge(p, cur, w);
		cur = p;
	}

	delete[] dist;
	delete[] prev;
	delete[] visited;

	return result;
}