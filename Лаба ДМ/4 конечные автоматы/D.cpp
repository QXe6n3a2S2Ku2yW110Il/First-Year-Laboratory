#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int MOD = 1e9 + 7;
 
struct matrix {
    int n, m;
    vector<vector<int>> a;
  
    matrix(int x, int y): n(x), m(y) {
        a.resize(x, vector<int>(y, 0));
    }
  
    matrix operator *(const matrix &b) const {
        //assert(m != b.n);
  
        matrix res = matrix(n, b.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                int currElement = 0;
                for (int k = 0; k < m; ++k)
                    currElement = (int)((currElement + (long long)a[i][k] * b.a[k][j]) % MOD);
  
                res.a[i][j] = currElement;
            }
        }
  
        return res;
    }
};
 
matrix binPow(matrix &a, long long n) {
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
 
int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
     
    int n, m, k, l;
    scanf("%d%d%d%d", &n, &m, &k, &l);
 
    vector<int> terminals;
    while (k--) {
        int v;
        scanf("%d", &v);
        terminals.push_back(--v);
    }
 
    matrix graph = matrix(n, n);// answer for l = 1
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
 
        ++graph.a[--from][--to];
    }
 
    matrix res = binPow(graph, l);
 
    int ans = 0;
    for (int v : terminals)
        ans = (ans + res.a[0][v]) % MOD;
     
    printf("%d", ans);
 
    return 0;
}
