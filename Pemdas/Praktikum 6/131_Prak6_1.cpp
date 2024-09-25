#include <iostream>
using namespace std;

int main() {
    int x, y;

    cout << "x: ";
    cin >> x;
    
    cout << "y: ";
    cin >> y;
    cout << endl;

    int *X = &x;
    int *Y = &y;

    int temp = *X;
    *X = *Y;
    *Y = temp;

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    return 0;
}
