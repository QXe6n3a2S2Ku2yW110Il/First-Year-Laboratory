#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int MOD = (int)1e9;
 
int main() {
    // freopen("sequences.in", "r", stdin);
    // freopen("sequences.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int left = 0; left < n - len + 1; ++left) {
            int right = left + len - 1;
 
            dp[left][right] = (dp[left][right] + dp[left + 1][right]) % MOD;
            dp[left][right] = (dp[left][right] + dp[left][right - 1]) % MOD;
            dp[left][right] = (dp[left][right] - dp[left + 1][right - 1]) % MOD;
            dp[left][right] = (dp[left][right] + MOD) % MOD;
            if (a[left] == a[right])
                dp[left][right] = (dp[left][right] + dp[left + 1][right - 1] + 1) % MOD;
        }
    }
 
    printf("%d", dp[0][n - 1]);
 
    return 0;
}
