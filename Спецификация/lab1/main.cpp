#include <iostream>
using namespace std;
int main() {
    int from, to;
    cin >> from;
    cin >> to;
    string neibs = "123456789876543210";
    for(int i = from; i <= to; i++){
        if (neibs.find(to_string(i)) != string::npos) {
            cout << i << endl;
        }
    }
}