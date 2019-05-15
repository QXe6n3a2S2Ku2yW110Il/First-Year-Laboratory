#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
const long long INF = (long long)1e16;
 
vector<vector<int>> save;
vector<vector<long long>> dp;
 
void writeString(string &s) {
    for (char c : s)
        printf("%c", c);
    printf("\n");
}
 
void rec(int left, int right, string s = "") {
    if (left == right) {
        writeString(s);
        return;
    }
 
    rec(left, save[left][right], s + "0");
    rec(save[left][right] + 1, right, s + "1");
}
 
int main() {
    freopen("optimalcode.in", "r", stdin);
    freopen("optimalcode.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> freq(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &freq[i]);
 
    vector<int> sumFreq(n + 1, 0);
    for (int i = 0; i < n; ++i)
        sumFreq[i + 1] = sumFreq[i] + freq[i];
 
    save.resize(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; ++i)
        save[i][i] = i;
    dp.resize(n + 1, vector<long long>(n + 1, INF));
    for (int i = 0; i < n;  ++i)
        dp[i][i] = 0;
    for (int len = 2; len <= n; ++len) {
        for (int left = 0; left < n - len + 1; ++left) {
            int right = left + len - 1;
 
            save[left][right] = save[left][right - 1];
            dp[left][right] = dp[left][save[left][right]] + dp[save[left][right] + 1][right];
            for (int k = save[left][right - 1] + 1; k <= save[left + 1][right]; ++k) {
                if (dp[left][right] >= dp[left][k] + dp[k + 1][right]) {
                    dp[left][right] = dp[left][k] + dp[k + 1][right];
                    save[left][right] = k;
                }
            }
 
            dp[left][right] += sumFreq[right + 1] - sumFreq[left];
        }
    }
 
    printf("%I64d\n", dp[0][n - 1]);
 
    rec(0, n - 1);
 
    return 0;
}
