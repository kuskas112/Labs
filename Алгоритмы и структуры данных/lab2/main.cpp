#include <iostream>
#include "List.h"

using namespace std;

class Student {
public:
	string family = "Ivanov";
	int ex1 = 5;
	int ex2 = 5;
	int ex3 = 5;
	bool hasHonorCertificate = false;
	string homeCity = "Moscow";
	bool needDormitory = false;
	string getKey() {
		return family;
	}
};

enum Descriptor{
	all = 0,
	exams = 1,
	certificate = 2,
	city = 3,
	dorimotory = 4
};

void showMenu() {
	cout << "1. Ввод записи об абитуриенте\n";
	cout << "2. Вывод подсписка\n";
	cout << "3. Вывод полного списка\n";
	cout << "4. Удаление записи об абитуриенте\n";
	cout << "5. Удаление всех записей\n";
	cout << "0. Выход\n";
}

void inputStudent(List<Student>& list) {
	// Ввод и заполнение Student, обработка ошибок всего такого
	// Для теста использую дефолтного
	Student st;
	// Сохраняю указатель на ноду для подсписков
	Node<Student>* node = list.insert(st); //Вставка в главный список

	// Вставка в подсписки
	if (st.ex1 == 5 && st.ex2 == 5 && st.ex3 == 5) { // Отличник
		list.insertByDescriptor(node, Descriptor::exams);
	}
	if (st.hasHonorCertificate) { // Аттестат с отличием
		list.insertByDescriptor(node, Descriptor::certificate);
	}
	if (st.homeCity != "Orel" && st.homeCity != "Орёл") { // Иногородний
		list.insertByDescriptor(node, Descriptor::city);
	}
	if (st.needDormitory) { // Нуждается в общаге
		list.insertByDescriptor(node, Descriptor::dorimotory);
	}

}

void showSubList(List<Student>& list) {
	char cmd;
	vector<Student> students;

	cout << "1. Вывести отличников" << endl;
	cout << "2. Вывести владельцев красного аттестата" << endl;
	cout << "3. Вывести иногородних" << endl;
	cout << "4. Вывести нуждающихся в общежитии" << endl;

	cin >> cmd;
		
	switch (cmd) {
	case '1':
		students = list.getAll(Descriptor::exams);
		break;
	case '2':
		students = list.getAll(Descriptor::certificate);
		break;
	case '3':
		students = list.getAll(Descriptor::city);
		break;
	case '4':
		students = list.getAll(Descriptor::dorimotory);
		break;
	default:
		cout << "Неверный номер подсписка" << endl;
	}


	for (int i = 0; i < students.size(); i++)
	{
		cout << students[i].family << endl;
	}
}

void main() {
	setlocale(LC_ALL, "rus");

	List<Student> list;

	// Вставка дескрипторов подсписков
	list.insertDescriptor(); // exams
	list.insertDescriptor(); // certificate
	list.insertDescriptor(); // city
	list.insertDescriptor(); // dorimotory

	char cmd;

	do {
		showMenu();
		cin >> cmd;

		switch (cmd) {
		case '1':
			inputStudent(list);
			break;
		case '2':
			showSubList(list);
			break;
		case '3':
			 //для полного списка getAll() либо getAll(Descriptors::all)
			break;
		case '0':
			cout << "Выход из программы.\n";
			break;
		default:
			cout << "Неверный выбор. Попробуйте еще раз.\n";
			break;
		}
	} while (cmd != '0');

}