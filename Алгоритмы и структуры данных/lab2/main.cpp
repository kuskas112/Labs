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
	cout << "1. ���� ������ �� �����������\n";
	cout << "2. ����� ���������\n";
	cout << "3. ����� ������� ������\n";
	cout << "4. �������� ������ �� �����������\n";
	cout << "5. �������� ���� �������\n";
	cout << "0. �����\n";
}

void inputStudent(List<Student>& list) {
	// ���� � ���������� Student, ��������� ������ ����� ������
	// ��� ����� ��������� ����������
	Student st;
	// �������� ��������� �� ���� ��� ����������
	Node<Student>* node = list.insert(st); //������� � ������� ������

	// ������� � ���������
	if (st.ex1 == 5 && st.ex2 == 5 && st.ex3 == 5) { // ��������
		list.insertByDescriptor(node, Descriptor::exams);
	}
	if (st.hasHonorCertificate) { // �������� � ��������
		list.insertByDescriptor(node, Descriptor::certificate);
	}
	if (st.homeCity != "Orel" && st.homeCity != "���") { // �����������
		list.insertByDescriptor(node, Descriptor::city);
	}
	if (st.needDormitory) { // ��������� � ������
		list.insertByDescriptor(node, Descriptor::dorimotory);
	}

}

void showSubList(List<Student>& list) {
	char cmd;
	vector<Student> students;

	cout << "1. ������� ����������" << endl;
	cout << "2. ������� ���������� �������� ���������" << endl;
	cout << "3. ������� �����������" << endl;
	cout << "4. ������� ����������� � ���������" << endl;

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
		cout << "�������� ����� ���������" << endl;
	}


	for (int i = 0; i < students.size(); i++)
	{
		cout << students[i].family << endl;
	}
}

void main() {
	setlocale(LC_ALL, "rus");

	List<Student> list;

	// ������� ������������ ����������
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
			 //��� ������� ������ getAll() ���� getAll(Descriptors::all)
			break;
		case '0':
			cout << "����� �� ���������.\n";
			break;
		default:
			cout << "�������� �����. ���������� ��� ���.\n";
			break;
		}
	} while (cmd != '0');

}