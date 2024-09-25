#include <iostream>
using namespace std;

int main() {
    int N;

    cin >> N;

    if( N % 4 == 0 && !( N % 100 == 0 )){
        cout << "Tahun Kabisat";
    }else if( N % 400 == 0 ){
        cout << "Tahun Kabisat";
    }else{
        cout << "Bukan Tahun Kabisat";
    }

    return 0;
}