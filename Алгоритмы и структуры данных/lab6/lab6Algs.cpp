#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath> // floor
#include <fstream>   // Для работы с файлами
using namespace std;
int r[6];
string* keys;
int* hashMap;
int mapSize = 997;
int keysAmount = 400;
int iterationLimit = 100;

string getKey() {
    char symbols[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int size = 62;
    string key = "";
    for (int i = 0; i < 6; i++)
    {
        key += symbols[rand() % size];
    }
    return key;
}

void clearHashMap(int map[], int size) {
    for (int i = 0; i < size; i++)
    {
        map[i] = 0;
    }
}

void getR(int arr[], int size) {
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 256;
    }
}

int xorMethod(string key, int r[]) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += (int)key[i] ^ r[i];
    }
    return sum;
}

int divideHashMethod(int M, int k) {
    return k % M;
}

int multiplyMethod(int M, int k) {
    float kA = 0.6180339887 * k;
    return M * (kA - floor(kA));
}

int linearMethod(string key, int (*hashMethod)(int, int), int hashParam, int c) {
    int k = xorMethod(key, r);
    int interationCntr = 0;
    while (interationCntr < iterationLimit)
    {
        int address = (hashMethod(hashParam, k) + (c * interationCntr++)) % mapSize;
        if (hashMap[address] == 0) {
            hashMap[address]++;
            return interationCntr;
        }
        else {
            int kek = 0;
        }
    }
    return -1;
}



int main() {
    setlocale(LC_ALL, "rus");
    srand(static_cast<unsigned int>(std::time(0))); // Инициализация генератора случайных чисел
    keys = new string[keysAmount];
    hashMap = new int[mapSize];
    getR(r, 6);
    clearHashMap(hashMap, mapSize);

    double sum = 0;
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = getKey();
        sum += linearMethod(keys[i], divideHashMethod, mapSize / 3, 139);
    }
    cout << "Средняя длина пути линейного метода + метода деления " << sum / keysAmount << endl;
    
    clearHashMap(hashMap, mapSize);

    sum = 0;
    for (int i = 0; i < keysAmount; i++)
    {
        sum += linearMethod(keys[i], multiplyMethod, mapSize, 139);
    }
    cout << "Средняя длина пути линейного метода + метода умножения " << sum / keysAmount << endl;

    ofstream outputFile("data.csv");

    if (!outputFile) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    for (int i = 0; i < mapSize; ++i) {
        outputFile << hashMap[i];
        if (i < mapSize - 1) { // Если это не последний элемент, добавляем запятую
            outputFile << ";";
        }
    }
    outputFile << endl;
    clearHashMap(hashMap, mapSize);

    return 0;
}
