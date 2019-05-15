#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("brackets2num.in", "r", stdin);
    freopen("brackets2num.out", "w", stdout);
 
    string s;
    cin >> s;
 
    int twoN = (int)s.length(), n = twoN / 2;        
 
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
 
    long long ans = 0;
    int balance = 0;
    for (int i = 0; i < twoN; ++i) {
        if (s[i] == '(')
            ++balance;
        else {
            if (balance + 1 <= n)
                ans += dp[twoN - i - 1][balance + 1];
            --balance;
        }
    }
 
    cout << ans;
 
    return 0;
}
