#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int MAX_NP1 = (1 << 7) + 1, LOG2_MAX_NP1 = 7 + 1, MOD = 1e9 + 7;
 
struct rect {
    int xL = 0, yL = 0, xR = 0, yR = 0;
    rect() = default;
    rect(int a, int b, int c, int d) : xL(a), yL(b), xR(c), yR(d) {}
};
 
rect unite(rect const& a, rect const& b) {
    if (a.xL > b.xR || a.xR < b.xL || a.yL > b.yR || a.yR < b.yL)
        return rect();
 
    int xL = max(a.xL, b.xL), xR = min(a.xR, b.xR);
    int yL = max(a.yL, b.yL), yR = min(a.yR, b.yR);
    return rect(xL, yL, xR, yR);
}
 
long long square(rect const& a) {
    return ((long long) (a.xR - a.xL) * (a.yR - a.yL)) % MOD;
}
 
rect st[MAX_NP1][MAX_NP1][LOG2_MAX_NP1][LOG2_MAX_NP1];
 
void write(rect const& a) {
    printf("rect %d %d %d %d\n", a.xL, a.yL, a.xR, a.yR);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    vector<vector<rect>> t(n, vector<rect>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            st[i][j][0][0] = t[i][j] = rect(min(a, c),
                                            min(b, d),
                                            max(a, c),
                                            max(b, d));
        }
    }
 
    vector<int> log2(MAX_NP1);
    for (int i = 2; i < MAX_NP1; ++i)
        log2[i] = log2[i / 2] + 1;
 
    for (int i = 0; i < n; ++i) {
        for (int lg = 1; lg <= log2[m]; ++lg) {
            for (int j = 0; j + (1 << (lg - 1)) < m; ++j)
                st[i][j][0][lg] = unite(st[i][j][0][lg - 1],
                                        st[i][j + (1 << (lg - 1))][0][lg - 1]);
        }
    }
 
    for (int k1 = 1; k1 <= log2[n]; ++k1) {
        for (int i = 0; i + (1 << (k1 - 1)) < n; ++i) {
            for (int k2 = 0; k2 <= log2[m]; ++k2) {
                for (int j = 0; j < m; ++j)
                    st[i][j][k1][k2] = unite(st[i][j][k1 - 1][k2],
                                             st[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
            }
        }
    }
 
    int q, a, b;
    scanf("%d%d%d", &q, &a, &b);
    int v[5];
    scanf("%d", &v[4]);
    int sum = 0;
    while (q--) {
        v[0] = v[4];
        for (int i = 1; i <= 4; ++i)
            v[i] = (int) (((long long) a * v[i - 1] + b) % MOD);
 
        int q1 = v[1] % n, q2 = v[2] % m, q3 = v[3] % n, q4 = v[4] % m;
        // printf("%d %d %d %d\n", q1, q2, q3, q4);
        int xL = min(q1, q3), yL = min(q2, q4);
        int xR = max(q1, q3), yR = max(q2, q4);
        int k1 = log2[xR - xL + 1], k2 = log2[yR - yL + 1];
        // printf("%d %d %d %d %d %d\n", xL, yL, xR, yR, k1, k2);
 
        rect ans1 = st[xL][yL][k1][k2];
        rect ans2 = st[xR - (1 << k1) + 1][yL][k1][k2];
        rect ans3 = st[xL][yR - (1 << k2) + 1][k1][k2];
        rect ans4 = st[xR - (1 << k1) + 1][yR - (1 << k2) + 1][k1][k2];
        // write(ans1);
        // write(ans2);
        // write(ans3);
        // write(ans4);
        rect ans = unite(unite(ans1, ans2), unite(ans3, ans4));
        // write(ans);
 
        sum = (int) ((sum + square(ans)) % MOD);
        // printf("%lld\n", square(ans));
    }
 
    printf("%d", sum);
 
    return 0;
}
