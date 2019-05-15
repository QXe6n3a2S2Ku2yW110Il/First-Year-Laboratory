#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("num2part.in", "r", stdin);
    freopen("num2part.out", "w", stdout);
 
    int n;
    long long r;
    scanf("%d%lld", &n, &r);
 
    long long dp[n + 1][n + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j)
            dp[i][j] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][i] = 1;
        for (int j = i - 1; j > -1; --j) {
            if (i - j > 0)
                dp[i][j] += dp[i - j][j];
            if (j < n)
                dp[i][j] += dp[i][j + 1];
        }
    }
 
    int pos = 1;
    vector<int> ans;
    while (n > 0) {
        while (pos < n && dp[n][pos] - dp[n][pos + 1] <= r) {
            r -= dp[n][pos] - dp[n][pos + 1];
            ++pos;
        }
        ans.push_back(pos);
        n -= pos;
    }
 
    for (int i = 0; i < (int)ans.size() - 1; ++i)
        printf("%d+", ans[i]);
    printf("%d", ans.back());
 
    return 0;
}
