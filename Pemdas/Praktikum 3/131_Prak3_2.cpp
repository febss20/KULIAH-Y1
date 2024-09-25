#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Masukan N: ";
    cin >> N;

    cout << "Tabel Perkalian Untuk " << N << ":" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++){
            int H = i * j;
            cout << i << " x " << j << " = " << H << endl;
        }
    }
    return 0;
}