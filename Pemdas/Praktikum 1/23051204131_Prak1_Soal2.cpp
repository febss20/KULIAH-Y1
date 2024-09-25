#include <iostream>
using namespace std;

int main (){
    const double PI = 3.14;
    int r, t;
    double v;

    cout << "Masukan Nilai jari-jari: ";
    cin >> r;

    cout << "Masukan Nilai tinggi: ";
    cin >> t;
    
    v = ( PI * r * r * t );
    cout << "volume tabung ini adalah: "<< v << endl;

    return 0;
}