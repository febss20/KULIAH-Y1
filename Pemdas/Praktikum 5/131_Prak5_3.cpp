#include <iostream>
#include <vector>
#include <string>

using namespace std;

int numDistinct(string s, string t) {
    int m = s.length();
    int n = t.length();

    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[m][n];
}

int main() {
    string s, t;

    cout << "Masukkan string (S): ";
    cin >> s;
    cout << "Masukkan string (T): ";
    cin >> t;

    cout << "Jumlah string T yang dapat disusun: " << numDistinct(s, t) << endl;

    return 0;
}
