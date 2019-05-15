#include <stdio.h>
#include <vector>
#include <assert.h>
 
using namespace std;
 
const int MOD = 999999937;
 
struct matrix {
    int n, m;
    vector<vector<int>> a;
 
    matrix(int x, int y): n(x), m(y) {
        a.resize(x, vector<int>(y, 0));
    }
 
    matrix operator *(const matrix &b) const {
        assert(m == b.n);
 
        matrix res = matrix(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                int currElement = 0;
                for (int k = 0; k < m; ++k)
                    currElement = (int)((currElement +
                    (long long)a[i][k] * b.a[k][j]) % MOD);
 
                res.a[i][j] = currElement;
            }
        }
 
        return res;
    }
};

matrix mul = matrix(5, 5);

matrix binPow(matrix a, long long n) {
    if (n == 0) {
        matrix one = matrix(a.n, a.n);
        for (int i = 0; i < a.n; ++i)
            one.a[i][i] = 1;

        return one;
    }

    if (n % 2 == 1) {
        return binPow(a, n - 1) * a;
    } else {
        matrix b = binPow(a, n / 2);
        return b * b;
    }
}

void solve(long long n) {
    if (n == 0)
        return;

    matrix start = matrix(5, 1);
    start.a = {
        {1},
        {1},
        {1},
        {1},
        {1}
    };

    start = binPow(mul, n - 1) * start;
    int ans = 0;
    for (int i = 0; i < 5; ++i)
        ans = (ans + start.a[i][0]) % MOD;

    printf("%d\n", ans);
}

int main() {
    mul.a = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 0, 1, 0},
        {1, 1, 0, 1, 0}
    };

    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);

    long long test = 1;
    while (test > 0) {
        scanf("%I64d", &test);
        solve(test);
    }

    return 0;
}
