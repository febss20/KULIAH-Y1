#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main () {
    double ch = 1;
    switch (ch)
    {
    case 1:
        ch++;
        break;

    case 2:
        ch--;
        break;
    }
    cout << ch;
}