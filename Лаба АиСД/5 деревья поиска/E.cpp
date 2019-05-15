#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct vert {
    int a = 0, b = 0, num = 0;
 
    vert() = default;
    vert(int x, int y, int i): a(x), b(y), num(i) {}
 
    bool operator <(const vert &v) const {
        if (a == v.a) {
            if (b == v.b)
                return num < v.num;
            return b < v.b;
        }
        return a < v.a;
    }
};
 
struct node {
    int key, prior, num;
    node *p, *l, *r;
 
    node(int k, int pr, int n, node *p_, node *l_, node *r_):
            key(k), prior(pr), num(n), p(p_), l(l_), r(r_) {}
    node(vert v, node *p_, node *l_, node *r_):
            key(v.a), prior(v.b), num(v.num), p(p_), l(l_), r(r_) {}
};
 
int getNum(node *tree) {
    if (tree == nullptr)
        return 0;
    return tree->num;
}
 
struct link {
    int p = 0, l = 0, r = 0;
 
    link() = default;
    link(node *tree): p(getNum(tree->p)),
                    l(getNum(tree->l)), r(getNum(tree->r)) {}
};
 
void traversal(node *tree, vector<link> &ans) {
    if (tree == nullptr)
        return;
 
    traversal(tree->l, ans);
    traversal(tree->r, ans);
 
    ans[tree->num - 1] = link(tree);
}
 
void clear(node *tree) {
    if (tree == nullptr)
        return;
 
    clear(tree->l);
    clear(tree->r);
 
    delete tree;
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<vert> v(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        v[i] = vert(x, y, i + 1);
    }
    sort(v.begin(), v.end());
 
    node *root = new node(v[0], nullptr, nullptr, nullptr);
    for (int i = 1; i < n; ++i) {
        if (root->prior < v[i].b) {
            root->r = new node(v[i], root, nullptr, nullptr);
            root = root->r;
        } else {
            node *tree = root;
            while (tree->p != nullptr && tree->prior >= v[i].b)
                tree = tree->p;
 
            if (tree->prior >= v[i].b) {
                root = new node(v[i], nullptr, tree, nullptr);
                tree->p = root;
            } else {
                root = new node(v[i], tree, tree->r, nullptr);
                tree->r = root;
                root->p = tree;
                root->l->p = root;
            }
        }
    }
    while (root->p != nullptr)
        root = root->p;
 
    vector<link> answer(n);
    traversal(root, answer);
 
    printf("YES\n");
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", answer[i].p, answer[i].l, answer[i].r);
 
    // clear(root);
 
    return 0;
}
