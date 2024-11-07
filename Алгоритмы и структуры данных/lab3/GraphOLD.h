#pragma once
#include <vector>


class Graph {
private:
	std::vector<char> vertexes;
	std::vector<std::vector<int>> adjacency;
public:
	std::vector<char> getVertexes() { return vertexes; }
	std::vector<std::vector<int>> getAdjacency() { return adjacency; }

	bool isEmpty() {
		return vertexes.size() <= 0;
	}

	int findVertex(char vert) {
		if (isEmpty()) return -1;

		for (int i = 0; i < vertexes.size(); i++) {
			if (vertexes[i] == vert) return i;
		}
		return -1;
	}

	bool addVertex(char vert) {
		if (findVertex(vert) != -1) return false;

		vertexes.push_back(vert);

		for (int i = 0; i < adjacency.size(); i++) {
			adjacency[i].push_back(0);
		}
		adjacency.push_back(std::vector<int>(adjacency.size() + 1, 0));
		return true;
	}

	bool delVertex(char vert) {
		int vertNum = findVertex(vert);
		if (vertNum == -1) return false;

		vertexes.erase(vertexes.begin() + vertNum);

		adjacency.erase(adjacency.begin() + vertNum);

		for (int i = 0; i < adjacency.size(); i++) {
			adjacency[i].erase(adjacency[i].begin() + vertNum);
		}
		return true;
	}


};