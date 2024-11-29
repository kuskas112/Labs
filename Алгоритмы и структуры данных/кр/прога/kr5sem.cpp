#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <vector>
#include <chrono>
#include <string>

#include "Record.h"
using namespace std;

class Timer {
private:
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
public:
	Timer() {
		this->start = chrono::high_resolution_clock::now();
	}
	double getDuration() {
		this->end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> elapsed = end - start;
		//cout << "Time: " << elapsed.count() << " ms\n";
		return elapsed.count();
	}
};

void createFin(int amount) {
	ofstream outfile("fin.bin", ios::binary | ios::trunc);
	for (int i = 0; i < amount; i++)
	{
		Record record;
		record.key = rand();
		outfile.write((char*)&record, sizeof(Record));
	}
	outfile.close();
}

void createF0() {
	ifstream fin("fin.bin", ios::binary);
	ofstream fout("f0.bin", ios::binary | ios::trunc);
	Record record;
	while(!fin.eof() && fin.read((char*)&record, sizeof(Record)))
	{
		fout.write((char*)&record, sizeof(Record));
	}
	fout.close();
	fin.close();
}

int printFile(const char* filename) {
	int cntr = 0;
	cout << "FILE: " << filename << endl;
	ifstream infile(filename, ios::binary);
	Record record;
	while (infile.read((char*)&record, sizeof(Record)) && !infile.eof()) {
		cout << record.key << endl;
		cntr++;
	}
	infile.close();
	cout << "--------------------------------" << endl;
	return cntr;
}

double directMerge() { //O(logn)
	Timer *timer = new Timer();
	fstream f0("f0.bin", ios::binary | ios::in);
	fstream f1, f2;
	Record record1, record2;
	f0.seekg(0, ios::end);
	auto len = f0.tellg() / sizeof(Record);
	f0.close();
	int i = 0, j = 0;
	int series = 1;

	while (series < len) {
		f0.open("f0.bin", ios::binary | ios::in);
		f1.open("f1.bin", ios::binary | ios::trunc | ios::out);
		f2.open("f2.bin", ios::binary | ios::trunc | ios::out);
		while (!f0.eof()) {
			i = 0;
			j = 0;
			while (!f0.eof() && i < series && f0.read((char*)&record1, sizeof(Record))) {
				i++;
				f1.write((char*)&record1, sizeof(Record));
			}
			while (!f0.eof() && j < series && f0.read((char*)&record1, sizeof(Record))) {
				j++;
				f2.write((char*)&record1, sizeof(Record));
			}
		}
		f0.close();
		f1.close();
		f2.close();

		f0.open("f0.bin", ios::binary | ios::trunc | ios::out);
		f1.open("f1.bin", ios::binary | ios::in);
		f2.open("f2.bin", ios::binary | ios::in);

		f1.read((char*)&record1, sizeof(Record));
		f2.read((char*)&record2, sizeof(Record));
		while (!f1.eof() && !f2.eof()) {
			i = 0;
			j = 0;
			while (i < series && j < series && !f1.eof() && !f2.eof()) {
				if (record1.key < record2.key) {
					f0.write((char*)&record1, sizeof(Record));
					f1.read((char*)&record1, sizeof(Record));
					i++;
				}
				else {
					f0.write((char*)&record2, sizeof(Record));
					f2.read((char*)&record2, sizeof(Record));
					j++;
				}
			}
			while (i < series && !f1.eof()) {
				f0.write((char*)&record1, sizeof(Record));
				f1.read((char*)&record1, sizeof(Record));
				i++;
			}
			while (j < series && !f2.eof()) {
				f0.write((char*)&record2, sizeof(Record));
				f2.read((char*)&record2, sizeof(Record));
				j++;
			}
		}
		while (!f1.eof()) {
			f0.write((char*)&record1, sizeof(Record));
			f1.read((char*)&record1, sizeof(Record));
		}
		while (!f2.eof()) {
			f0.write((char*)&record2, sizeof(Record));
			f2.read((char*)&record2, sizeof(Record));
		}

		f0.close();
		f1.close();
		f2.close();
		series *= 2;
	}
	double res = timer->getDuration();
	delete timer;
	return res;
}

double naturalMerge() {
	Timer *timer = new Timer();
	fstream f0, f1, f2;
	Record record1, record2;
	int s = 1;
	while (s > 0) {
		f0.open("f0.bin", ios::binary | ios::in);
		f1.open("f1.bin", ios::binary | ios::out | ios::trunc);
		f2.open("f2.bin", ios::binary | ios::out | ios::trunc);
		int lastKey = INT_MIN;
		bool currFile = true;
		s = 0;
		while (!f0.eof() && f0.read((char*)&record1, sizeof(Record))) {
			if (lastKey > record1.key) {
				currFile = !currFile;
				s++;
			}
			lastKey = record1.key;
			if (currFile) {
				f1.write((char*)&record1, sizeof(Record));
			}
			else {
				f2.write((char*)&record1, sizeof(Record));
			}
		}
		f0.close();
		f1.close();
		f2.close();

		f0.open("f0.bin", ios::binary | ios::out | ios::trunc);
		f1.open("f1.bin", ios::binary | ios::in);
		f2.open("f2.bin", ios::binary | ios::in);

		f1.read((char*)&record1, sizeof(Record));
		f2.read((char*)&record2, sizeof(Record));
		bool s1 = true, s2 = true;
		while (!f1.eof() && !f2.eof()) {
			if (s1 && s2) {
				if (record1.key < record2.key) {
					f0.write((char*)&record1, sizeof(Record));
					int oldKey = record1.key;
					f1.read((char*)&record1, sizeof(Record));
					if (record1.key < oldKey) s1 = false;
				}
				else {
					f0.write((char*)&record2, sizeof(Record));
					int oldKey = record2.key;
					f2.read((char*)&record2, sizeof(Record));
					if (record2.key < oldKey) s2 = false;
				}
			}
			else if (s1) {
				f0.write((char*)&record1, sizeof(Record));
				int oldKey = record1.key;
				f1.read((char*)&record1, sizeof(Record));
				if (record1.key < oldKey) s1 = false;
			}
			else if (s2) {
				f0.write((char*)&record2, sizeof(Record));
				int oldKey = record2.key;
				f2.read((char*)&record2, sizeof(Record));
				if (record2.key < oldKey) s2 = false;
			}
			else {
				s1 = s2 = true;
			}
		}
		if (!f1.eof()) f0.write((char*)&record1, sizeof(Record));
		while (!f1.eof() && f1.read((char*)&record1, sizeof(Record))) {
			f0.write((char*)&record1, sizeof(Record));
		}
		if (!f2.eof()) f0.write((char*)&record2, sizeof(Record));
		while (!f2.eof() && f2.read((char*)&record2, sizeof(Record))) {
			f0.write((char*)&record2, sizeof(Record));
		}
		f0.close();
		f1.close();
		f2.close();
	}
	double res = timer->getDuration();
	delete timer;
	return res;
}

int main()
{
	srand(static_cast<unsigned int>(std::time(0)));
	locale::global(std::locale("ru_RU.UTF-8"));
	cout.imbue(std::locale());
	ofstream fout("data.csv", ios::trunc);
	fout << "Прямое слияние;Естественное слияние\n";
	for (int i = 0; i < 100; i++)
	{
		createFin(10000);
		createF0();
		double directRes = directMerge();

		createF0();
		double naturalRes = naturalMerge();
		fout << directRes << ";" << naturalRes << endl;
	}
	
	fout.close();
	/*total = printFile("f0.bin");
	cout << "TOTAL: " << total << endl;*/
	
}