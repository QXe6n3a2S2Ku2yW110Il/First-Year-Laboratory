#include <stdio.h>
#include <vector>
 
using namespace std;
 
int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
 
    int n, m;
    scanf("%d%d", &n, &m);
 
    vector<int> w(n), c(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &w[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &c[i]);
 
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    vector<vector<int>> prev(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            prev[i][j] = j;
            if (j - w[i - 1] >= 0 && dp[i - 1][j - w[i - 1]] > -1) {
                if (dp[i][j] < dp[i - 1][j - w[i - 1]] + c[i - 1]) {
                    dp[i][j] = dp[i - 1][j - w[i - 1]] + c[i - 1];
                    prev[i][j] = j - w[i - 1];
                }
            }
        }
    }
 
    int nPos = n, mPos = m, currMax = -1;
    for (int j = 0; j <= m; ++j) {
        if (currMax < dp[n][j]) {
            currMax = dp[n][j];
            mPos = j;
        }
    }
    if (currMax == -1) {
        printf("Pomelo");
        return 0;
    }
 
    vector<int> ans;
    while (nPos > 0) {
        if (mPos != prev[nPos][mPos])
            ans.push_back(nPos);
        mPos = prev[nPos][mPos];
        --nPos;
    }
 
    printf("%d\n", (int)ans.size());
    for (int i : ans)
        printf("%d ", i);
 
    return 0;
}
