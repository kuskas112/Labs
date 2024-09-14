#include <iostream>
#include <string>
#include "QueueList.h"
#include <vector>
using namespace std;
class Detail {
public:
    void inputDetail() {
        string inCode = getValidString();
        for (int i = 0; i < 4; i++)
        {
            this->code[i] = inCode[i];
        }
        this->code[4] = '\0';
        this->time = getValidNumber();
    }
    char code[5] = "----";
    int time = 0;
    
private:
    int getValidNumber() {
        int number;
        while (true) {
            cout << "Введите время: ";
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
    string getValidString() {
        string input;
        while (true) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите код детали: ";
            getline(cin, input);

            if (input.length() >= 4) {
                return input.substr(0, 4);
            }
            else {
                cout << "Ошибка: строка должна содержать ровно 4 символа!" << endl;
                //cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

};


int main()
{
    setlocale(LC_ALL, "ru");
    Queue<Detail> queue;
    string menu =
        "\n1. Постановка на обработку\n"
        "2. Временной переход\n"
        "3. Снять деталь\n"
        "4. Посмотреть очередь\n"

        "0. Выход\n"
    ;

    while (true) {
        cout << menu;
        string cmd;
        cin >> cmd;

        if (cmd == "0") {
            return 0;
        }
        else if (cmd == "1") {
            Detail det;
            det.inputDetail();
            if (queue.insert(det)) {
                cout << "Успешно!" << endl;
            }
            else {
                cout << "Очередь переполнена" << endl;
            }
        }
        else if (cmd == "2") {
            Detail* det = queue.peek();
            if (det != nullptr) {
                det->time--;
                if (det->time <= 0) {
                    cout << "Деталь с кодом " << det->code << " закончила обработку" << endl;
                    queue.dequeue();
                }
            }
        }
        else if (cmd == "3") {
            Detail* det = queue.peek();
            if (det != nullptr) {
                cout << "Деталь с кодом " << det->code << " преждевременно снята" << endl;
                queue.dequeue();
            }
            else {
                cout << "Очередь пуста" << endl;
            }
        }
        else if (cmd == "4") {
            vector<Detail> arr;
            queue.getQueue(arr);
            if (arr.size() == 0) {
                cout << "Очередь пуста" << endl;
            }
            for (int i = 0; i < arr.size(); i++)
            {
                cout << ">> Code: " << arr[i].code << "; Time Remaining: " << arr[i].time << endl;
            }
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }

}
