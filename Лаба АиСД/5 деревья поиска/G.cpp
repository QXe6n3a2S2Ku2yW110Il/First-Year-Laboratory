#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const int MAX_N = (int) 1e9;
 
struct node {
    long long key;
    int prior;
    node *l;
    node *r;
    int subtreeSize;
    long long sum;
 
    node(long long k, int p, int s, long long sm):
            key(k), prior(p), l(nullptr), r(nullptr), subtreeSize(s), sum(sm) {}
};
 
node *root = nullptr;
 
int getSubtreeSize(node *tree) {
    if (tree == nullptr)
        return 0;
    return tree->subtreeSize;
}
 
long long getSum(node *vertex) {
    if (vertex == nullptr)
        return 0;
    return vertex->sum;
}
 
void update(node *tree) {
    if (tree == nullptr)
        return;
 
    tree->subtreeSize = getSubtreeSize(tree->l) + getSubtreeSize(tree->r) + 1;
    tree->sum = getSum(tree->l) + getSum(tree->r) + tree->key;
}
 
pair<node *, node *> split(node *tree, long long key) {
    if (tree == nullptr)
        return {nullptr, nullptr};
    if (tree->key < key) {
        pair<node *, node *> tmp = split(tree->r, key);
        tree->r = tmp.first;
        update(tmp.second);
        update(tree);
        return {tree, tmp.second};
    } else {
        pair<node *, node *> tmp = split(tree->l, key);
        tree->l = tmp.second;
        update(tmp.first);
        update(tree);
        return {tmp.first, tree};
    }
}
 
node *merge(node *L, node *R) {
    if (L == nullptr)
        return R;
    if (R == nullptr)
        return L;
 
    if (L->prior > R->prior) {
        L->r = merge(L->r, R);
        update(L);
        return L;
    } else {
        R->l = merge(L, R->l);
        update(R);
        return R;
    }
}
 
node *insert(node *vertex) {
    pair<node *, node *> one_two;
    one_two = split(root, vertex->key);
 
    one_two.first = merge(one_two.first, vertex);
    return merge(one_two.first, one_two.second);
}
 
bool search(node *tree, long long key) {
    if (tree == nullptr)
        return false;
    if (tree->key == key)
        return true;
 
    if (tree->key > key)
        return search(tree->l, key);
    return search(tree->r, key);
}
 
int main() {
    int m;
    scanf("%d", &m);
 
    long long ans = 0;
    char prevC = 'h';
    while (m--) {
        char c;
        scanf("\n%c", &c);
 
        if (c == '+') {
            long long x;
            scanf("%I64d", &x);
 
            if (prevC == '?') {
                if (!search(root, (x + ans) % MAX_N)) {
                    node *vertex = new node((x + ans) % MAX_N, rand(), 1, (x + ans) % MAX_N);
                    root = insert(vertex);
                }
            } else {
                if (!search(root, x)) {
                    node *vertex = new node(x, rand(), 1, x);
                    root = insert(vertex);
                }
            }
        }
        if (c == '?') {
            int left, right;
            scanf("%d%d", &left, &right);
 
            auto tmp = split(root, left);
            auto tmpp = split(tmp.second, right + 1);
 
            printf("%I64d\n", ans = (tmpp.first == nullptr ? 0LL : tmpp.first->sum));
 
            tmp.second = merge(tmpp.first, tmpp.second);
            root = merge(tmp.first, tmp.second);
        }
 
        prevC = c;
    }
 
    return 0;
}
