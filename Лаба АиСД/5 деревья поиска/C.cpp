#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct node {
    int prior;
    node *l;
    node *r;
    int subtreeSize;
    int val;
 
    node(int p, int s, int v) : prior(p), l(nullptr), r(nullptr),
                                subtreeSize(s), val(v) {}
};
 
node *root = nullptr;
 
int getSubtreeSize(node *tree) {
    if (tree == nullptr)
        return 0;
    return tree->subtreeSize;
}
 
void update(node *tree) {
    if (tree == nullptr)
        return;
 
    tree->subtreeSize = getSubtreeSize(tree->l) + getSubtreeSize(tree->r) + 1;
}
 
pair<node *, node *> split(node *tree, int key) {
    if (tree == nullptr)
        return {nullptr, nullptr};
 
    if (getSubtreeSize(tree->l) == key) {
        node *tmp = tree->l;
        tree->l = nullptr;
        update(tree);
        return {tmp, tree};
    }
    if (getSubtreeSize(tree->l) > key) {
        auto tmp = split(tree->l, key);
        tree->l = tmp.second;
        update(tree);
        return {tmp.first, tree};
    } else {
        auto tmp = split(tree->r, key - getSubtreeSize(tree->l) - 1);
        tree->r = tmp.first;
        update(tree);
        return {tree, tmp.second};
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
 
int get(node *tree, int ind) {
    if (tree == nullptr)
        return 55555555;
 
    int tmp = getSubtreeSize(tree->l);
    if (tmp == ind)
        return tree->val;
    if (tmp >= ind)
        return get(tree->l, ind);
    return get(tree->r, ind - (tmp + 1));
}
 
// insert to back
node *insert(node *vertex) {
    return merge(root, vertex);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    for (int i = 0; i < n; ++i) {
        node *vertex = new node(rand(), 1, i + 1);
        root = insert(vertex);
    }
 
    while (m--) {
        int left, right;
        scanf("%d%d", &left, &right);
 
        auto tmp = split(root, --left);
        auto tmpp = split(tmp.second, right - left);
        tmp.second = merge(tmp.first, tmpp.second);
        root = merge(tmpp.first, tmp.second);
    }
 
    for (int i = 0; i < n; ++i)
        printf("%d ", get(root, i));
 
    return 0;
}
