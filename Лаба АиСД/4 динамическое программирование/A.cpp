#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
struct threeple {
    int left = 0, middle = 0, right = 0;
 
    threeple() = default;
    threeple(int a, int b, int c) : left(a), middle(b), right(c) {}
};
 
void writeString(string s) {
    for (char c : s)
        printf("%c", c);
}
 
vector<vector<threeple>> prevPos;
string writeAns(int left, int right) {
    // printf("%d %d\n", left, right);
    if (right - left < 2) {
        string ans;
        for (int i = 0; i <= right - left; ++i)
            ans += "A";
        return ans;
    }
 
    auto prev = prevPos[left][right];
    string ans;
    if (prev.left == prev.middle)
        ans += "A";
    else
        ans += "(" + writeAns(prev.left, prev.middle) + ")";
    if (prev.middle + 1 == prev.right)
        ans += "A";
    else
        ans += "(" + writeAns(prev.middle + 1, prev.right) + ")";
 
    return ans;
}
 
int main() {
    const int INF = (int)1e9;
 
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    if (n == 1) {
        printf("A");
        return 0;
    }
 
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d", &a[i], &b[i]);
 
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 1; i < n; ++i)
        dp[i - 1][i] = a[i - 1] * a[i] * b[i];
    prevPos.resize(n, vector<threeple>(n));
    for (int len = 3; len <= n; ++len) {
        for (int left = 0; left <= n - len; ++left) {
            int right = left + len - 1;
 
            int withL = dp[left][right - 1] + a[left] * a[right] * b[right];
            int withR = dp[left + 1][right] + a[left] * b[left] * b[right];
            if (withR < withL) {
                dp[left][right] = withR;
                prevPos[left][right] = threeple(left, left, right);
            } else {
                dp[left][right] = withL;
                prevPos[left][right] = threeple(left, right - 1, right);
            }
 
            for (int middle = left + 1; middle < right; ++middle) {
                int add = a[left] * b[middle] * b[right];
                if (dp[left][right] > dp[left][middle] + dp[middle + 1][right] + add) {
                    dp[left][right] = dp[left][middle] + dp[middle + 1][right] + add;
                    prevPos[left][right] = threeple(left, middle, right);
                }
            }
        }
    }
 
    writeString("(" + writeAns(0, n - 1) + ")");
 
    return 0;
}
