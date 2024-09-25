#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string string1, string2;
    cin >> string1 >> string2;

    if (string1.length() != string2.length()) {
        cout << "BUKAN" << endl;
        return 0;
    }

    sort(string1.begin(), string1.end());
    sort(string2.begin(), string2.end());

    if (string1 == string2) {
        cout << "YA" << endl;
    } else {
        cout << "BUKAN" << endl;
    }

    return 0;
}
