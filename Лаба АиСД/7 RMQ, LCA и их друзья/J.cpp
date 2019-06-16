#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const int N = 2e6 + 1, INF = 1e9 + 7, MIN_POS = -1e6, MAX_POS = 1e6;
 
struct node {
    int qty, pos, add_val;
};
node tree[4 * N];
 
void choose(int i) {
    if (tree[2 * i + 1].qty > tree[2 * i + 2].qty) {
        tree[i].qty = tree[2 * i + 1].qty;
        tree[i].pos = tree[2 * i + 1].pos;
    } else {
        tree[i].qty = tree[2 * i + 2].qty;
        tree[i].pos = tree[2 * i + 2].pos;
    }
}
 
void init_tree(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i].qty = tree[i].add_val = 0;
        tree[i].pos = L;
        return;
    }
 
    int M = L + (R - L) / 2;
    init_tree(2 * i + 1, L, M);
    init_tree(2 * i + 2, M, R);
    choose(i);
}
 
void push(int i, int L, int R) {
    if (L + 1 < R) {
        tree[2 * i + 1].qty += tree[i].add_val;
        tree[2 * i + 1].add_val += tree[i].add_val;
        tree[2 * i + 2].qty += tree[i].add_val;
        tree[2 * i + 2].add_val += tree[i].add_val;
    }
    tree[i].add_val = 0;
}
 
void update(int i, int L, int R, int l, int r, int val) {
    if (L >= r || R <= l)
        return;
    if (l <= L && R <= r) {
        tree[i].qty += val;
        tree[i].add_val += val;
        return;
    }
 
    push(i, L, R);
    int M = L + (R - L) / 2;
    update(2 * i + 1, L, M, l, r, val);
    update(2 * i + 2, M, R, l, r, val);
    choose(i);
}
 
int main() {
    init_tree(0, MIN_POS, MAX_POS + 1);
 
    int n;
    scanf("%d", &n);
 
    struct segment {
        int x = 0, y1 = 0, y2 = 0;
        // bottom left -> false, upeer right -> true
        bool type = false;
 
        segment() = default;
        segment(int a, int b, int c, bool d): x(a), y1(b), y2(c), type(d) {}
 
        bool operator<(const segment &s) const {
            if (x == s.x)
                return type < s.type;
            return x < s.x;
        }
    };
 
    vector<segment> segments(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        int leftX, leftY, rightX, rightY;
        scanf("%d%d%d%d", &leftX, &leftY, &rightX, &rightY);
 
        segments[i] = segment(leftX, leftY, rightY, false);
        segments[++i] = segment(rightX, leftY, rightY, true);
    }
 
    sort(segments.begin(), segments.end());
 
    int ansQty = 0, ansX = 0, ansY = 0;
    for (auto &s : segments) {
        if (s.type == false) {
            update(0, MIN_POS, MAX_POS + 1, s.y1, s.y2 + 1, 1);
            if (tree[0].qty > ansQty) {
                ansQty = tree[0].qty;
                ansX = s.x;
                ansY = tree[0].pos;
            }
        } else {
            update(0, MIN_POS, MAX_POS + 1, s.y1, s.y2 + 1, -1);
        }
    }
 
    printf("%d\n%d %d", ansQty, ansX, ansY);
 
    return 0;
}
