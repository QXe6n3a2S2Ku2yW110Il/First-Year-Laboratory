#include <stdio.h>
#include <string>
#include <vector>
 
using namespace std;
 
bool readString(string &s) {
    s.clear();
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
 
    return !s.empty();
}
 
int mod = 2147483647;
struct matrix {
    int x11, x12, x21, x22;
    matrix() = default;
    matrix(int a, int b, int c, int d):
        x11(a % mod), x12(b % mod), x21(c % mod), x22(d % mod) {}
    matrix operator*(const matrix &m) const {
        return matrix(
            (x11 * m.x11 + x12 * m.x21) % mod,
            (x11 * m.x12 + x12 * m.x22) % mod,
            (x21 * m.x11 + x22 * m.x21) % mod,
            (x21 * m.x12 + x22 * m.x22) % mod);
    }
};
const matrix ONE = matrix(1, 0, 0, 1);
 
vector<matrix> a, tree;
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = a[L];
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    tree[i] = tree[2 * i + 1] * tree[2 * i + 2];
}
 
matrix get_prod(int i, int L, int R, int l, int r) {
    if (L >= r || R <= l)
        return ONE;
    if (l <= L && R <= r)
        return tree[i];
 
    int M = L + (R - L) / 2;
    return get_prod(2 * i + 1, L, M, l, r) * get_prod(2 * i + 2, M, R, l, r);
}
 
void set_val(int i, int L, int R, int ind, matrix &val) {
    if (L > ind || R < ind)
        return;
    if (L + 1 == R) {
        if (L == ind)
            tree[i] = val;
        return;
    }
 
    int M = L + (R - L) / 2;
    set_val(2 * i + 1, L, M, ind, val);
    set_val(2 * i + 2, M, R, ind, val);
    tree[i] = tree[2 * i + 1] * tree[2 * i + 2];
}
 
int main() {
    int n, m;
    scanf("%d%d%d", &mod, &n, &m);
 
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        int c, l, o, j;
        scanf("%d%d%d%d", &c, &l, &o, &j);
 
        a[i] = matrix(c, l, o, j);
    }
 
    tree.resize(4 * n, ONE);
    init_tree(0, 0, n);
 
    while (m--) {
        int left, right;
        scanf("%d%d", &left, &right);
 
        matrix res = get_prod(0, 0, n, --left, right);
        printf("%d %d\n%d %d\n\n", res.x11, res.x12, res.x21, res.x22);
    }
 
    return 0;
}
