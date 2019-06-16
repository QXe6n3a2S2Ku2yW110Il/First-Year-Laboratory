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
 
const int INF = 1e9 + 7;
 
vector<int> tree;
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = R;
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
}
 
int get_min(int i, int L, int R, int l, int r) {
    if (L >= r || R <= l)
        return INF;
    if (l <= L && R <= r)
        return tree[i];
 
    int M = L + (R - L) / 2;
    return min(get_min(2 * i + 1, L, M, l, r), get_min(2 * i + 2, M, R, l, r));
}
 
void update(int i, int L, int R, int ind, int val) {
    if (L > ind || R < ind)
        return;
    if (L + 1 == R) {
        if (L == ind)
            tree[i] = val;
        return;
    }
 
    int M = L + (R - L) / 2;
    update(2 * i + 1, L, M, ind, val);
    update(2 * i + 2, M, R, ind, val);
    tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    tree.resize(4 * n);
    init_tree(0, 0, n);
 
    string query;
    while (m--) {
        scanf("\n");
        readString(query);
        int pos, ans;
        scanf("%d", &pos);
 
        switch (query[1]) {
            case 'n':
                ans = get_min(0, 0, n, --pos, n);
                if (ans == INF)
                    ans = get_min(0, 0, n, 0, pos);
                update(0, 0, n, ans - 1, INF);
                printf("%d\n", ans);
                break;
            case 'x':
                update(0, 0, n, pos - 1, pos);
                break;
        }
    }
 
    return 0;
}
