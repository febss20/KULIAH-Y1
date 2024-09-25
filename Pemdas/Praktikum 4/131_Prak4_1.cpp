#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int catatan_waktu[N];

    for (int i = 0; i < N; i++) {
        cin >> catatan_waktu[i];
    }
    cout << endl;

    for (int i = N - 1; i >= 0; i--) {
        cout << catatan_waktu[i] << endl;
    }

    return 0;
}
