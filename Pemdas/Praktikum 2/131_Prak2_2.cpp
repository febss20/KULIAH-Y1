#include <iostream>
using namespace std;

int main (){
    int N;

    cin >> N;

    if( N > 0 ){
        cout << "Bilangan Bulat Positif";
    }else if( N < 0 ){
        cout << "Bilangan Bulat Negatif";
    }else{
        cout << "Nol";
    }

    return 0;
}