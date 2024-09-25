#include <iostream>

using namespace std;

int main (){
    int a, x;
    cout << "input 10 buah bilangan" << endl;
    cout << "bilangan pertama: ";
    cin >> a;
    x = a;
        
    for (int i = 1; i <= 9; i++){
        cout << "bilangan ke-" << i+1 << " : ";
        cin >> a;
        if ( a < x){
            x = a;
        }
        
}
    cout << x;
    return 0;
}