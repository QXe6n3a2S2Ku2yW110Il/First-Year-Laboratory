#include <bits/stdc++.h>
 
using namespace std;
 
inline unsigned long long exp2(int x) {
    return (1ULL << x);
}
 
int main() {
    freopen("num2brackets2.in", "r", stdin);
    freopen("num2brackets2.out", "w", stdout);
 
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
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
 
    vector<char> stack;
    int balance = 0;
    for (int i = twoN - 1; i > -1; --i) {
        long long ratio;
        if (balance < n)
            ratio = dp[i][balance + 1] * exp2((i - balance - 1) / 2);
        else
            ratio = 0;
        if (ratio >= k) {
            printf("(");
            stack.push_back('(');
            ++balance;
            continue;
        }
        k -= ratio;
 
        if ((int)stack.size() > 0 && stack.back() == '(' && balance > 0)
            ratio = dp[i][balance - 1] * exp2((i - balance + 1) / 2);
        else
            ratio = 0;
        if (ratio >= k) {
            printf(")");
            stack.pop_back();
            --balance;
            continue;
        }
        k -= ratio;
 
        if (balance < n)
            ratio = dp[i][balance + 1] * exp2((i - balance - 1) / 2);
        else
            ratio = 0;
        if (ratio >= k) {
            printf("[");
            stack.push_back('[');
            ++balance;
            continue;
        }
        k -= ratio;
 
        printf("]");
        stack.pop_back();
        --balance;
    }
 
    return 0;
}
