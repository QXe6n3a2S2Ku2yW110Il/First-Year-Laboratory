#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
void readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
}
 
int main() {
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
 
    string s, t;
    readString(s);
    readString(t);
 
    int n = (int)s.length(), m = (int)t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= m; ++i)
        dp[0][i] = i;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = i;
        for (int j = 1; j <= m; ++j)
            dp[i][j] = min(dp[i - 1][j - 1] + (s[i - 1] != t[j - 1]),
                           min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
    }
 
    printf("%d", dp[n][m]);
 
    return 0;
}
