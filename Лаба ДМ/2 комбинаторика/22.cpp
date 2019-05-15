#include <bits/stdc++.h>
 
using namespace std;
 
int stringToInt(string &s) {
    int res = 0;
    for (char c : s)
        res = res * 10 + (c - '0');
 
    return res;
}
 
int main() {
    freopen("part2num.in", "r", stdin);
    freopen("part2num.out", "w", stdout);
 
    char c;
    string currNum;
    vector<int> nums(1, 0);
    int n = 0;
    while (scanf(" \n%c", &c) == 1) {
        if (c == '+') {
            nums.push_back(stringToInt(currNum));
            n += nums.back();
            currNum = "";
        }
        else
            currNum += c;
    }
    nums.push_back(stringToInt(currNum));
    n += nums.back();
 
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
 
    long long ans = 0;
    for (int i = 1; i < (int)nums.size(); ++i) {
        ans += dp[n][nums[i - 1]] - dp[n][nums[i]];
        n -= nums[i];
    }
 
    printf("%lld", ans);
 
    return 0;
}
