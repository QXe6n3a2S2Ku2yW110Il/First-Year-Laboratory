#include <stdio.h>
#include <vector>
 
using namespace std;
 
int x, a, y, b, qty;
 
bool check(int z) {
    vector<vector<int>> dp(x + 1, vector<int>(y + 1));
    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            for (int k = 0; k <= i; ++k) {
                int tmp = (z - k * a) / b + ((z - k * a) % b > 0);
                tmp = max(0, tmp);
                if (j >= tmp)
                    dp[i][j] = max(dp[i][j], dp[i - k][j - tmp] + 1);
            }
        }
    }
 
    return dp[x][y] >= qty;
}
 
int binSearch(int leftArg, int rightArg) {
    int left = leftArg, right = rightArg + 1;
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (check(middle))
            left = middle;
        else
            right = middle;
    }
 
    return left;
}
 
int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
 
    scanf("%d%d%d%d%d", &x, &a, &y, &b, &qty);
 
    printf("%d", binSearch(min(a, b), x * a + y * b));
 
    return 0;
}
