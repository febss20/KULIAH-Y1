#include <iostream>

using namespace std;

long long virtualFactorial(int n, int v) {
    long long result = 1;
    while (n > 0) {
        result *= n;
        n -= v;
    }
    return result;
}

int main() {
    int t; 
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n, v; 
        cin >> n >> v;

        long long result = virtualFactorial(n, v);

        cout << result << endl;
    }

    return 0;
}
