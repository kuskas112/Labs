#pragma once
#include <vector>

struct vertex {
	char name;
	std::vector<vertex*> links;
	vertex* next = nullptr;

	vertex(char name) {
		this->name = name;
	}

	~vertex() {
		next = nullptr;

		for (vertex* v : links) {
			delete v;
		}

		links.clear();

	}
};

class Graph {
private:
	vertex* head = nullptr;
	vertex* tail = nullptr;
	size_t size = 0;

public:

	friend void showGraph(Graph* graph);
	friend void readFromFile(Graph* graph);

	bool isEmpty() {
		return head == nullptr;
	}

	vertex* findVertex(char name, vertex** vertPrev = nullptr) {
		if (isEmpty()) return nullptr;

		vertex* curVert = head;
		while (curVert != nullptr) {
			if (curVert->name == name) return curVert;

			if (vertPrev) {
				*vertPrev = curVert;
			}
			
			curVert = curVert->next;
		}

		return nullptr;
	}

	vertex* findLink(vertex* vert, vertex* vertTarget, vertex** vertPrev = nullptr) {
		auto links = vert->links;

		for (auto l : links) {
			if (l->name == vertTarget->name) return l;
			
			if (vertPrev) {
				*vertPrev = l;
			}
		}
		return nullptr;
	}

	bool findLink(char vert, char vertTarget) {
		vertex* vertLink = findVertex(vert);

		for (auto l : vertLink->links) {
			if (l->name == vertTarget) return true;
		}

		return false;
	}

	bool addVertex(char name) {
		if (findVertex(name) != nullptr) return false;

		vertex* newVertex = new vertex(name);
		if (isEmpty()) {
			head = newVertex;
			tail = newVertex;
		}
		else {
			tail->next = newVertex;
			tail = newVertex;
		}

		size++;
		return true;
	}

	bool delVertex(char name) {
		vertex* vertPrev = nullptr;
		vertex* vert = findVertex(name, &vertPrev);
		if (vert == nullptr) return false;

		if (vert == head) {
			head = vert->next;
		}
		else if (vert == tail) {
			tail = vertPrev;
			tail->next = nullptr;
		}
		else {
			vertPrev->next = vert->next;
		}

		delete vert;
		size--;


		return true;
	}

	int addLink(char name1, char name2) {
		vertex* vert1 = findVertex(name1); 
		vertex* vert2 = findVertex(name2);
		if (vert1 == nullptr || vert2 == nullptr) return -1; // if no vertex
		if (findLink(vert1, vert2) != nullptr) return -2; // if link alredy exists

		vert1->links.push_back(vert2);

		return 1;
	}


	void clear() {
		vertex* currVert = head;
		while (currVert != nullptr) {
			vertex* next = currVert->next;

			delete currVert;

			currVert = next;
		}

		head = nullptr;
		tail = nullptr;
		size = 0;
	}

};