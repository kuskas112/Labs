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

enum Descriptor {
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

	// Вставка в подсписки

	cout << "Введите фамилию студента" << endl;
	cin >> st.family;
	cout << "Введите оценки за три экзамена" << endl;
	cin >> st.ex1;
	cin >> st.ex2;
	cin >> st.ex3;
	cout << "Есть ли у студента аттестат с отличием (Д/Н)" << endl;
	char cert;
	cin >> cert;
	cout << "Введите название населенного пункта, в котором проживает студент" << endl;
	cin >> st.homeCity;

	if (cert == 'д' || cert == 'Д' || cert == 'Y' || cert == 'y') {
		st.hasHonorCertificate = true;
	}
	else {
		st.hasHonorCertificate = false;
	}

	Node<Student>* node = list.insert(st); //Вставка в главный список


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

void insertStudent(List<Student>& list, Student st) { //для отладки нужна была
	Node<Student>* node = list.insert(st); //Вставка в главный список

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

void showList(List<Student>& list) {
	for (auto i : list.getAll()) {
		cout << i.family << endl;
	}
}

void deleteNode(List<Student>& list) {
	string st;
	cout << "Введите ключ записи, которую надо удалить" << endl;
	cin >> st;
	list.deleteNode(st);
}

void deleteAll(List<Student>& list) {
	list.clear();
}

int main() {
	setlocale(LC_ALL, "Russian");

	List<Student> list;

	// Вставка дескрипторов подсписков
	list.insertDescriptor(); // exams
	list.insertDescriptor(); // certificate
	list.insertDescriptor(); // city
	list.insertDescriptor(); // dorimotory

	char cmd;

	do {
		system("cls");
		showMenu();
		cin >> cmd;

		switch (cmd) {
		case '1':
			// Добавить информацию о студенте
			inputStudent(list);
			break;
		case '2':
			// Вывод подсписков
			showSubList(list);
			break;
		case '3':
			// Вывод полного списка
			showList(list);
			break;
		case '4':
			// Удаление записи
			deleteNode(list);
			break;
		case '5':
			// Удаление всех записей
			deleteAll(list);
			break;
		case '0':
			cout << "Выход из программы.\n";
			break;
		default:
			cout << "Неверный выбор. Попробуйте еще раз.\n";
			break;
		}
		system("pause");
	} while (cmd != '0');

}