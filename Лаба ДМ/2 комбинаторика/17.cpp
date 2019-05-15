#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("num2brackets.in", "r", stdin);
    freopen("num2brackets.out", "w", stdout);
 
    int n;
    long long k;
    cin >> n >> k;
    ++k;
    int twoN = 2 * n;
 
    long long dp[twoN + 1][n + 1];// dp[i][j], i - length, j - balance
    for (auto &i : dp) {
        for (auto &j : i)
            j = 0;
    }
    dp[0][0] = 1;
    for (int i = 0; i < twoN; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (j + 1 <= n)
                dp[i + 1][j + 1] += dp[i][j];
            if (j > 0)
                dp[i + 1][j - 1] += dp[i][j];
        }
    }
 
    string ans = "";
    int balance = 0;
    for (int i = twoN - 1; i > -1; --i) {
        if (balance + 1 <= n && dp[i][balance + 1] >= k) {
           ans += '(';
           ++balance;
        } else {
            if (balance + 1 <= n)
                k -= dp[i][balance + 1];
            ans += ')';
            --balance;
        }
    }
 
    cout << ans;
 
    return 0;
}
