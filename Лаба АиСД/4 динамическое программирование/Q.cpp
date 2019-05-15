#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
struct bigInt {
    vector<int> a;
 
    bigInt() {
        a.resize(107, 0);
    }
    bigInt(string &s) {
        a.resize(107, 0);
        a[0] = (int)s.length();
        for (int i = 1; i <= a[0]; ++i)
            a[i] = (int)((char)s[a[0] - i] - '0');
    }
 
    bigInt operator -(int b) const {
        int r = 0;
        bigInt c;
        c.a[0] = a[0];
 
        for (int i = 1; i <= a[0]; ++i) {
            c.a[i] = a[i] - (b % 10 + r);
 
            if (c.a[i] < 0) {
                r = 1;
                c.a[i] += 10;
            } else {
                r = 0;
            }
 
            b /= 10;
        }
 
        while (c.a[0] > 1 && c.a[c.a[0]] == 0)
            --c.a[0];
 
        return c;
    }
 
    bigInt operator /(const int b) const {
        int r = 0;
 
        bigInt c;
        c.a[0] = a[0];
 
        for (int i = c.a[0]; i > 0; --i) {
            r = r * 10 + a[i];
            c.a[i] = r / b;
            r %= b;
        }
 
        while (c.a[0] > 1 && c.a[c.a[0]] == 0)
            --c.a[0];
 
        return c;
    }
};
 
int mod;
struct matrix {
    int n, m;
    vector<vector<int>> a;
 
    matrix(int x, int y): n(x), m(y) {
        a.resize(x, vector<int>(y, 0));
    }
 
    matrix operator *(const matrix &b) const {
        matrix res = matrix(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                int currElement = 0;
                for (int k = 0; k < m; ++k)
                    currElement = (int)((currElement +
                    (long long)a[i][k] * b.a[k][j]) % mod);
 
                res.a[i][j] = currElement;
            }
        }
 
        return res;
    }
};
 
matrix binPow(matrix a, bigInt &n) {
    if (n.a[0] == 0 || (n.a[1] == 0 && n.a[0] == 1)) {
        matrix one = matrix(a.n, a.n);
        for (int i = 0; i < a.n; ++i)
            one.a[i][i] = 1;
 
        return one;
    }
 
    if (n.a[1] % 2 == 1) {
        n = n - 1;
        return binPow(a, n) * a;
    } else {
        n = n / 2;
        matrix b = binPow(a, n);
        return b * b;
    }
}
 
void writeString(string &s) {
    for (char c : s)
        printf("%c", c);
    printf("\n");
}
 
void readBigInt(bigInt &x) {
    char c;
    string s;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
 
    x = bigInt(s);
}
 
void writeBigInt(bigInt &x) {
    for (int i = x.a[0]; i > 0; --i)
        printf("%d", x.a[i]);
    printf("\n");
}
 
int m;
bool ok(int p, int p1) {
    for (int i = 0; i < m - 1; ++i) {
        if (((p >> i) & 1) == ((p1 >> i) & 1) &&
            ((p >> (i + 1)) & 1) == ((p1 >> (i + 1)) & 1) &&
            ((p >> i) & 1) == ((p >> (i + 1)) & 1))
            return false;
    }
 
    return true;
}
 
int main() {
    freopen("nice3.in", "r", stdin);
    freopen("nice3.out", "w", stdout);
 
    bigInt n;
    readBigInt(n);
    scanf("%d%d", &m, &mod);
 
    int pow2m = (1 << m);
    matrix mul = matrix(pow2m, pow2m);
    for (int x = 0; x < pow2m; ++x) {
        for (int y = 0; y < pow2m; ++y)
            mul.a[x][y] = ok(x, y);
    }
 
    matrix start = matrix(pow2m, 1);
    for (int i = 0; i < pow2m; ++i)
        start.a[i][0] = 1;
 
    n = n - 1;
    start = binPow(mul, n) * start;
    int ans = 0;
    for (int i = 0; i < pow2m; ++i)
        ans = (ans + start.a[i][0]) % mod;
 
    printf("%d", ans);
 
    return 0;
}
