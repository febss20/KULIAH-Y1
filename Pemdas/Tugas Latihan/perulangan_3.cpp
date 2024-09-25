#include <iostream>
using namespace std;

//int main (){
    //int counter, sum, N;
    //cout << "Enter the number of positive integers : ";
    //cin >> N;
    //sum = 0;
    
    //for ( counter = 1; counter <= N; counter++ )
        //sum = sum + counter;
        //cout << "the sum of the first " << N << " positive integers is " << sum << endl;
    
    //return 0;
//}

int main() {
    int counter = 1, sum = 0, N;
    cout << "Enter the number of positive integers: ";
    cin >> N;
    sum = 0;

    while (counter <= N) {
        sum = sum + counter;
        counter++;
    }

    cout << "The sum of the first " << N << " positive integers is " << sum << endl;

    return 0;
}
