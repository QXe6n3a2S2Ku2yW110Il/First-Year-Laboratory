#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("num2choose.in", "r", stdin);
    freopen("num2choose.out", "w", stdout);
 
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
    long long m;
    scanf("%d%d%lld", &n, &k, &m);
    int currNum = 1;
    while (k > 0) {
        if (m < c[n - 1][k - 1]) {
            printf("%d ", currNum);
            --k;
        }
        else
            m -= c[n - 1][k - 1];
        --n;
        ++currNum;
    }
 
    return 0;
}
