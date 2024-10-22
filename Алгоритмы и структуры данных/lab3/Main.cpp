#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <iomanip>

#include "Graph.h"

using namespace std;

/*
void showGraph(Graph* graph) {
	if (graph->isEmpty()) {
		cout << "���� �� �������� �� ����� �������" << endl;
		return;
	}

	const int gap = 6;

	cout << setw(gap) << ' ';
	auto vertexes = graph->getVertexes();
	auto adjacency = graph->getAdjacency();
	for (int i = 0; i < vertexes.size(); i++) {
		cout << setw(gap) << vertexes[i];
	}
	cout << endl;

	for (int i = 0; i < vertexes.size(); i++) {
		cout << setw(gap) << vertexes[i];
		for (int j = 0; j < adjacency[i].size(); j++) {
			cout << setw(gap) << adjacency[i][j];
		}
		cout << endl;
	}
}
*/

void showGraph(Graph* graph) {
	vertex* vert = graph->head;
	while (vert != nullptr) {
		cout << vert->name << " -> {";
		for (auto v : vert->links) {
			cout << v->name << ", ";
		}
		cout << "}" << endl;
		vert = vert->next;
	}
	cout << endl;
}

void readFromFile(Graph* graph) {
	graph->clear();
	ifstream inFile("data.txt");

	if (!inFile) {
		cerr << "�� ������� ������� ���� ��� ������" << endl;
		return;
	}

	string line, st;
	getline(inFile, line);
	stringstream ss(line);
	while (getline(ss, st, ',')) {
		graph->addVertex((char)st[0]);
	}

	vertex* currVert = graph->head;
	while (getline(inFile, line)) {
		vertex* link = graph->head;
		stringstream sstream(line);
		string el;
		while (getline(sstream, el, ',')) {
			char connectValue = el[0];
			if (connectValue != '0') {
				currVert->links.push_back(link);
			}
			link = link->next;
		}

		currVert = currVert->next;
	}

	cout << "������ �������" << endl;
}

void addVertex(Graph* graph) {
	cout << "������� ����� �������: ";
	char vert;
	cin >> vert;
	if (!graph->addVertex(vert)) cout << "������� ��� ����������" << endl;
}

void delVertex(Graph* graph) {
	cout << "������� �������, ������� ����� �������: ";
	char vert;
	cin >> vert;
	if (!graph->delVertex(vert)) cout << "����� ������� �� ����������" << endl;
}

void addLink(Graph* graph) {
	char vert1, vert2;
	cout << "������� ������� 1: ";
	cin >> vert1;
	cout << endl;
	cout << "������� ������� 2: ";
	cin >> vert2;
	cout << endl;

	int resp = graph->addLink(vert1, vert2);
	if (resp == -1) {
		cout << "�� ��� ������ �������";
	}
	else if (resp == -2) {
		cout << "����� ��� ����������";
	}
	else {
		cout << "����� ���������";
	}
	cout << endl;
}

void findLink(Graph* graph) {
	char vert1, vert2;
	cout << "������� ������� 1: ";
	cin >> vert1;
	cout << endl;
	cout << "������� ������� 2: ";
	cin >> vert2;
	cout << endl;

	if (graph->findLink(vert1, vert2)) {
		cout << "����� �������" << endl;
	}
	else {
		cout << "����� �� �������" << endl;
	}
}

void showMenu() {
	cout<< "1. ��������\n"
		<< "2. ������� �� �����\n"
		<< "3. �������� �������\n"
		<< "4. ������� �������\n"
		<< "5. �������� �����\n"
		<< "6. ����� �����\n"
		<< endl
		<< "0. �����\n"
		;
}


int main() {
	setlocale(LC_ALL, "Russian");
	char fun = '0';
	Graph graph;

	graph.addVertex('a');
	graph.addVertex('b');
	graph.addVertex('c');
	graph.addVertex('d');
	
	while (1) {
		system("cls");

		showMenu();
		cin >> fun;

		system("cls");
		switch (fun)
		{
		case '1':
			showGraph(&graph);
			break;
		case '2':
			readFromFile(&graph);
			break;
		case '3':
			addVertex(&graph);
			break;
		case '4':
			delVertex(&graph);
			break;
		case '5':
			addLink(&graph);
			break;
		case '6':
			findLink(&graph);
			break;
		case '0':
			return 0;
		default:
			cout << "������� �������� �������" << endl;
			break;
		}
		system("pause");
	}
}