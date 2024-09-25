#include <iostream>
using namespace std;

int main() {
    cout << "KELUARAN Anda - KELUARAN Penguji" << endl;
    cout << "                1 10" << endl;

    int harga = 7;

    for (int m = 1; m <= 15; m++) {
        int tebakan;

        cin >> tebakan;

        if(tebakan > harga) {
            cout << "                terlalu besar" << endl;
        } else if(tebakan < harga) {
            cout << "                terlalu kecil" << endl;
        } else {
            cout << "                nah bener lu gw maapin" << endl;
            break;
        }
    }
    return 0;
}
