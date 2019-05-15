#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
const int INF = (int)1e8;
 
void readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
}
 
bool symbol(char c) {
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}
 
int main() {
    // freopen("sequences.in", "r", stdin);
    // freopen("sequences.out", "w", stdout);
 
    string s, t;
    readString(s);
    readString(t);
    s = " " + s;
    t = " " + t;
 
    int n = (int)s.length(), m = (int)t.length();
    // true only if dp[i][j] == j
    vector<vector<bool>> dp(n, vector<bool>(m, false));
    dp[0][0] = true;
    for (int i = 1; i < n && s[i] == '*'; ++i)
        dp[i][0] = true;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - 1];
            } else {
                if (symbol(s[i]))
                    dp[i][j] = false;
                if (s[i] == '?')
                    dp[i][j] = dp[i][j] || dp[i - 1][j - 1];
                if (s[i] == '*')
                    dp[i][j] = dp[i][j] || dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }
 
    printf((dp[n - 1][m - 1] ? "YES" : "NO"));
 
    return 0;
}
