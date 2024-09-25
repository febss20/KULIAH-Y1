#include <iostream>
#include <string>
using namespace std;

struct Hiu {
    string nama;
    string buahKesukaan;
};

int main() {
    int N;
    cin >> N;

    Hiu hiuList[N];

    for (int i = 0; i < N; i++) {
        cin >> hiuList[i].nama >> hiuList[i].buahKesukaan;
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        if (hiuList[i].buahKesukaan == "Tomato") {
            cout << hiuList[i].nama << endl;
        }
    }

    return 0;
}
