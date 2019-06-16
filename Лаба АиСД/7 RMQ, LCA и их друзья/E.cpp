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
 
vector<long long> a, tree;
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = a[L];
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
}
 
long long get_sum(int i, int L, int R, int l, int r) {
    if (L >= r || R <= l)
        return 0;
    if (l <= L && R <= r)
        return tree[i];
 
    int M = L + (R - L) / 2;
    return get_sum(2 * i + 1, L, M, l, r) + get_sum(2 * i + 2, M, R, l, r);
}
 
void set_val(int i, int L, int R, int ind, long long val) {
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
    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    a.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%I64d", &a[i]);
 
    tree.resize(4 * n, 0);
    init_tree(0, 0, n);
 
    scanf("\n");
    string query;
    while (readString(query)) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        switch (query[1]) {
            case 'u':
                printf("%I64d\n", get_sum(0, 0, n, --x, y));
                break;
            case 'e':
                set_val(0, 0, n, --x, y);
                break;
        }
 
        scanf("\n");
    }
 
    return 0;
}
