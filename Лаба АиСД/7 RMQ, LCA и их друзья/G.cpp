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
 
const long long INFL = 5e18 + 7e10;
 
struct node {
    long long min_ = INFL, add_val = 0, set_val = 0;
    bool need_set = false;
    node() = default;
};
 
vector<long long> a;
vector<node> tree;
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i].min_ = a[L];
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    tree[i].min_ = min(tree[2 * i + 1].min_, tree[2 * i + 2].min_);
}
 
void push(int i, int L, int R) {
    if (tree[i].need_set) {
        tree[2 * i + 2].min_ = tree[2 * i + 1].min_ = tree[i].set_val;
        if (L + 1 < R) {
            tree[2 * i + 2].set_val = tree[2 * i + 1].set_val = tree[i].set_val;
            tree[2 * i + 2].need_set = tree[2 * i + 1].need_set = true;
            tree[2 * i + 2].add_val = tree[2 * i + 1].add_val = 0;
        }
        tree[i].need_set = false;
    }
 
    if (L + 1 < R) {
        tree[2 * i + 1].min_ += tree[i].add_val;
        tree[2 * i + 1].add_val += tree[i].add_val;
        tree[2 * i + 2].min_ += tree[i].add_val;
        tree[2 * i + 2].add_val += tree[i].add_val;
    }
    tree[i].add_val = 0;
}
 
long long get_min(int i, int L, int R, int l, int r) {
    if (L >= r || R <= l)
        return INFL;
    if (l <= L && R <= r)
        return tree[i].min_;
 
    push(i, L, R);
    int M = L + (R - L) / 2;
    return min(get_min(2 * i + 1, L, M, l, r), get_min(2 * i + 2, M, R, l, r));
}
 
void update(int i, int L, int R, int l, int r, long long val, bool set) {
    if (L >= r || R <= l)
        return;
    if (l <= L && R <= r) {
        if (set) {
            tree[i].set_val = tree[i].min_ = val;
            tree[i].need_set = true;
            tree[i].add_val = 0;
        } else {
            tree[i].min_ += val;
            tree[i].add_val += val;
        }
        return;
    }
 
    push(i, L, R);
    int M = L + (R - L) / 2;
    update(2 * i + 1, L, M, l, r, val, set);
    update(2 * i + 2, M, R, l, r, val, set);
    tree[i].min_ = min(tree[2 * i + 1].min_, tree[2 * i + 2].min_);
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    a.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%I64d", &a[i]);
 
    tree.resize(4 * n);
    init_tree(0, 0, n);
 
    scanf("\n");
    string query;
    while (readString(query)) {
        int left, right;
        long long val;
        scanf("%d%d", &left, &right);
        switch (query[0]) {
            case 'm':
                printf("%I64d\n", get_min(0, 0, n, --left, right));
                break;
            case 's':
                scanf("%I64d", &val);
                update(0, 0, n, --left, right, val, true);
                break;
            case 'a':
                scanf("%I64d", &val);
                update(0, 0, n, --left, right, val, false);
                break;
        }
        scanf("\n");
    }
 
    return 0;
}
