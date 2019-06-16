#include <stdio.h>
#include <string>
#include <vector>
 
using namespace std;
 
const int INF = (int) 1e9 + 7;
 
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
 
vector<int> a, tree;
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = a[L];
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
}
 
int get_min(int i, int L, int R, int l, int r) {
    // printf("in [%d..%d)\n", L, R);
    if (L >= r || R <= l) {
        // printf("out [%d..%d) = INF\n", L, R);
        return INF;
    }
    if (l <= L && R <= r) {
        // printf("out [%d..%d) = %d\n", L, R, tree[i]);
        return tree[i];
    }
 
    int M = L + (R - L) / 2;
    return min(get_min(2 * i + 1, L, M, l, r), get_min(2 * i + 2, M, R, l, r));
}
 
void set_val(int i, int L, int R, int ind, int val) {
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
    tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    a.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    tree.resize(4 * n, INF);
    init_tree(0, 0, n);
 
    scanf("\n");
    string query;
    while (readString(query)) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        switch (query[0]) {
            case 'm':
                printf("%d\n", get_min(0, 0, n, --x, y));
                break;
            case 's':
                set_val(0, 0, n, --x, y);
                break;
        }
 
        // for (int i : tree)
        //    printf("%d ", i);
        // printf("\n");
 
        scanf("\n");
    }
 
    return 0;
}
