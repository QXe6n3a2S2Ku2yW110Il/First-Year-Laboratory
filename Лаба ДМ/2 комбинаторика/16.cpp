#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("choose2num.in", "r", stdin);
    freopen("choose2num.out", "w", stdout);
 
    long long c[40][40];// c(n, k)
    for (int i = 0; i < 40; ++i) {
        c[i][0] = 1;
        for (int j = 1; j < 40; ++j)
            c[i][j] = 0;
    }
    for (int i = 1; i < 40; ++i) {
        for (int j = 1; j <= i; ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
 
    int n, k;
    scanf("%d%d", &n, &k);
 
    long long ans = 0;
    int xPrev = 0;
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
 
        for (int j = xPrev + 1; j < x; ++j)
            ans += c[n - j][k - i - 1];
 
        xPrev = x;
    }
 
    printf("%lld", ans);
 
    return 0;
}
