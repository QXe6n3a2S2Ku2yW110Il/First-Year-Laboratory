#include <bits/stdc++.h>
 
using namespace std;
 
void readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1)
        s += c;
    if (c == '\n' || c == ' ')
        s.pop_back();
}
 
unsigned long long exp2(int x) {
    return (1ULL << x);
}
 
int main() {
    freopen("brackets2num2.in", "r", stdin);
    freopen("brackets2num2.out", "w", stdout);
 
    string s;
    readString(s);
 
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
 
    int balance = 0;
    vector<char> stack;
    long long ans = 0;
    for (int i = twoN - 1; i > -1; --i) {
        if (s[twoN - 1 - i] == '(') {
            stack.push_back('(');
            ++balance;
            continue;
        }
 
        if (balance < n)
            ans += dp[i][balance + 1] * exp2((i - balance - 1) / 2);
        if (!stack.empty() && stack.back() == '(' && s[twoN - 1 - i] == ')') {
            stack.pop_back();
            --balance;
            continue;
        }
 
        if (!stack.empty() && stack.back() == '(' && balance > 0)
            ans += dp[i][balance - 1] * exp2((i - balance + 1) / 2);
        if (s[twoN - 1 - i] == '[') {
            stack.push_back('[');
            ++balance;
            continue;
        }
 
 
        if (balance < n)
            ans += dp[i][balance + 1] * exp2((i - balance - 1) / 2);
        stack.pop_back();
        --balance;
    }
 
    printf("%lld", ans);
 
    return 0;
}
