#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// Fungsi untuk menghitung F(n)
pair<int, int> calculateF(int n) {
    if (n == 0) {
        return {1, 0};
    } else if (n == 1) {
        return {2, 0};
    }

    int f_n_minus_1, f_n_minus_2, total_calls;

    tie(f_n_minus_1, total_calls) = calculateF(n - 1);
    tie(f_n_minus_2, ignore) = calculateF(n - 2);

    int result;
    if (n % 5 == 0) {
        result = n * 2;
    } else {
        result = f_n_minus_1 + n + f_n_minus_2 + n - 2;
        if (n % 3 == 0) {
            total_calls++;
        }
    }

    return {result, total_calls};
}

int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        int N;
        cin >> N;

        pair<int, int> result = calculateF(N);

        cout << "Case #" << i << ": " << result.first << " " << result.second << endl;
    }

    return 0;
}
