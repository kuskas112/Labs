#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Tree.h"

using namespace std;

void readNumbersFromFile(const string& filename, Tree& tree) {
    ifstream file(filename);

    // Проверка на успешное открытие файла
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }

    string line;
    // Чтение файла построчно
    while (getline(file, line)) {
        istringstream iss(line);
        int number;

        // Чтение целых чисел из строки
        while (iss >> number) {
            tree.insert(number);
        }
    }

    file.close(); // Закрытие файла
}

int getValidNumber() {
	int number;
	while (true) {
		cout << "Введите число: ";
		cin >> number;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ошибка: введите корректное целое число!" << endl;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return number;
}

void showMenu() {
	cout << "Меню:" << endl;
	cout << "1. Добавить в дерево" << endl;
	cout << "2. Вывести дерево" << endl;
	cout << "3. Вычислить высоту" << endl;
	cout << "4. Поиск вершин, у которых количество потомков в левом поддереве отличается от количества потомков в правом поддереве на единицу" << endl;
	cout << "5. Поиск k-го в порядке слева направо листа дерева" << endl;
	cout << "6. Удаление вершины" << endl;
	cout << "0. Выход" << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    string filename = "numbers.txt";
    Tree tree;

    readNumbersFromFile(filename, tree);

	char cmd;

	do {
		system("cls");
		showMenu();
		cin >> cmd;

		switch (cmd) {
		case '1':
			tree.insert(getValidNumber());
			break;
		case '2':
			tree.print();
			break;
		case '3':
			cout << "Высота дерева: " << tree.findHeight() << endl;
			break;
		case '4':
			tree.findUnbalancedNodes();
			break;
		case '5':
			tree.findKthLeaf(getValidNumber());
			break;
		case '6':
			tree.deleteNode(getValidNumber());
			break;
		case '0':
			cout << "Выход из программы.\n";
			return 0;
		default:
			cout << "Неверный выбор. Попробуйте еще раз.\n";
			break;
		}
		system("pause");
	} while (cmd != '0');
}
