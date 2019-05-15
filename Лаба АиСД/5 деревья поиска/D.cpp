#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct node {
    int key;
    int prior;
    node *l;
    node *r;
    int subtreeSize;
 
    node(int k, int p, int s) : key(k), prior(p),
                                l(nullptr), r(nullptr), subtreeSize(s) {}
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
 
node *erase(int key) {
    pair<node *, node *> one_two;
    one_two = split(root, key);
 
    node *three = one_two.first;
    // one_two.first - erasable vertex
    one_two = split(one_two.second, key + 1);
    return merge(three, one_two.second);
}
 
bool search(node *tree, int key) {
    if (tree == nullptr)
        return false;
    if (tree->key == key)
        return true;
 
    if (tree->key > key)
        return search(tree->l, key);
    return search(tree->r, key);
}
 
int kth(node *tree, int k) {
    int tmp = getSubtreeSize(tree->r);
 
    if (tmp == k)
        return tree->key;
    if (tmp < k)
        return kth(tree->l, k - (tmp + 1));
    return kth(tree->r, k);
}
 
int main() {
    int m;
    scanf("%d", &m);
 
    while (m--) {
        int x, k;
        scanf("%d%d", &x, &k);
 
        if (x > 0) {
            node *vertex = new node(k, rand(), 1);
            root = insert(vertex);
        }
        if (x < 0)
            root = erase(k);
        if (x == 0)
            printf("%d\n", kth(root, k - 1));
    }
 
    return 0;
}
