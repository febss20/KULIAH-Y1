#include <iostream>
using namespace std;

int main() {
    int N, K;

    cout << "Masukkan (N): ";
    cin >> N;
    cout << "Masukkan (K): ";
    cin >> K;

    //cin >> N >> K;
    
    cout << "Status lampu: " << endl;
    for (int i =1; i <= N; i++) {
        if (i % K == 0) {
            cout << "* ";
        } else {
            cout << i << " ";
        }
    }
    return 0;
}
