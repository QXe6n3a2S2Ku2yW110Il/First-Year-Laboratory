#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

struct matrix {
    int n, m;
    vector<vector<double>> a;

    matrix(int x, int y): n(x), m(y) {
        a.resize(x, vector<double>(y, 0));
    }

    matrix operator *(const matrix &b) const {
        matrix res = matrix(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                double currElement = 0;
                for (int k = 0; k < m; ++k)
                    currElement += a[i][k] * b.a[k][j];

                res.a[i][j] = currElement;
            }
        }

        return res;
    }
};

int main() {
    const double EPS = 1e-5;
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);

    int n;
    scanf("%d", &n);
    
    matrix p = matrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            scanf("%lf", &p.a[i][j]);
    }

    while (true) {
        matrix sqrP = p * p;
        bool satisfy = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (abs(sqrP.a[i][j] - p.a[i][j]) > EPS)
                    satisfy = false;
            }
        }

        if (satisfy)
            break;
        
        p = sqrP;
    }

    for (int i = 0; i < n; ++i)
        printf("%.5lf\n", p.a[0][i]);

    return 0;
}
