#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
 
using namespace std;
 
bool readString(string &s) {
    s = "";
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == '\n' || c == ' ')
            break;
 
        s += c;
    }
 
    return s.length() > 0;
}
 
struct node {
    int value, level;
    node *left, *right, *anc;
 
    node(int v, int l, node *l_, node *r_, node *a_):
            value(v), level(l), left(l_), right(r_), anc(a_) {}
};
 
node *root = nullptr;
 
node* skew(node *tree) {
    if (tree == nullptr)
        return nullptr;
    if (tree->left == nullptr)
        return tree;
 
    if (tree->left->level == tree->level) {
        node *left = tree->left;
        node *anc = tree->anc;
        left->anc = anc;
        tree->left = left->right;
        if (tree->left != nullptr)
            tree->left->anc = tree;
        left->right = tree;
        tree->anc = left;
 
        if (anc != nullptr) {
            if (anc->left == tree)
                anc->left = left;
            else
                anc->right = left;
        }
 
        return left;
    }
 
    return tree;
}
 
node* split(node *tree) {
    if (tree == nullptr)
        return nullptr;
    if (tree->right == nullptr || tree->right->right == nullptr)
        return tree;
 
    if (tree->level == tree->right->right->level) {
        node *right = tree->right;
        node *anc = tree->anc;
        right->anc = tree->anc;
        tree->right = right->left;
        if (tree->right != nullptr)
            tree->right->anc = tree;
        right->left = tree;
        tree->anc = right;
        ++right->level;
 
        if (anc != nullptr) {
            if (anc->left == tree)
                anc->left = right;
            else
                anc->right = right;
        }
 
        return right;
    }
 
    return tree;
}
 
node* insert(node *tree, int x) {
    if (tree == nullptr)
        return new node(x, 1, nullptr, nullptr, nullptr);
    /*if (tree->value == x)
        return tree;*/
 
    if (x < tree->value) {
        tree->left = insert(tree->left, x);
        tree->left->anc = tree;
    } else if (x > tree->value) {
        tree->right = insert(tree->right, x);
        tree->right->anc = tree;
    }
 
    tree = skew(tree);
    tree = split(tree);
 
    return tree;
}
 
node* decreaseLevel(node *tree) {
    --tree->level;
    if (tree->right != nullptr && tree->right->level > tree->level)
        tree->right->level = tree->level;
 
    return tree;
}
 
node* erase(node *tree, int x) {
    if (tree == nullptr)
        return tree;
 
    if (x > tree->value) {
        tree->right = erase(tree->right, x);
        if (tree->right != nullptr)
            tree->right->anc = tree;
    } else if (x < tree->value) {
        tree->left = erase(tree->left, x);
        if (tree->left != nullptr)
            tree->left->anc = tree;
    } else {
        if (tree->left == nullptr && tree->right == nullptr) {
            delete tree;
            return nullptr;
        }
 
        if (tree->left == nullptr) {
            auto tmp = tree->right;
            while (tmp->left != nullptr)
                tmp = tmp->left;
 
            tree->value = tmp->value;
            tree->right = erase(tree->right, tmp->value);
            if (tree->right != nullptr)
                tree->right->anc = tree;
        } else {
            auto tmp = tree->left;
            while (tmp->right != nullptr)
                tmp = tmp->right;
 
            tree->value = tmp->value;
            tree->left = erase(tree->left, tmp->value);
            if (tree->left != nullptr)
                tree->left->anc = tree;
        }
    }
 
    if ((tree->left != nullptr && tree->left->level < tree->level - 1) ||
        (tree->right != nullptr && tree->right->level < tree->level - 1)) {
            tree = decreaseLevel(tree);
            tree = skew(tree);
            tree->right = skew(tree->right);
            if (tree->right != nullptr)
                tree->right->right = skew(tree->right->right);
            tree = split(tree);
            tree->right = split(tree->right);
        }
 
    return tree;
}
 
node* exists(node *tree, int x) {
    if (tree == nullptr)
        return nullptr;
 
    if (tree->value == x)
        return tree;
    if (tree->value < x)
        return exists(tree->right, x);
    return exists(tree->left, x);
}
 
node* next(node *tree, int x) {
    node *vertex = exists(tree, x);
    if (vertex->right == nullptr) {
        while (vertex->anc != nullptr && vertex == vertex->anc->right)
            vertex = vertex->anc;
 
        return vertex->anc;
    } else {
        vertex = vertex->right;
        while (vertex->left != nullptr)
            vertex = vertex->left;
 
        return vertex;
    }
}
 
node* prev(node *tree, int x) {
    node *vertex = exists(tree, x);
    if (vertex->left == nullptr) {
        while (vertex->anc != nullptr && vertex == vertex->anc->left)
            vertex = vertex->anc;
 
        return vertex->anc;
    } else {
        vertex = vertex->left;
        while (vertex->right != nullptr)
            vertex = vertex->right;
 
        return vertex;
    }
}
 
void print(node *tree) {
    if (tree == nullptr)
        return;
 
    print(tree->left);
    print(tree->right);
 
    printf("%d ", tree->value);
}
 
int main() {
    string s;
    while (readString(s)) {
        int x;
        scanf("%d", &x);
 
        if (s == "insert")
            root = insert(root, x);
        if (s == "delete") {
            root = erase(root, x);
            if (root != nullptr)
                root->anc = nullptr;
        }
        if (s == "exists")
            printf((exists(root, x) == nullptr ? "false\n" : "true\n"));
        if (s == "next") {
            bool exist = exists(root, x);
            if (!exist)
                root = insert(root, x);
 
            node *result = next(root, x);
            if (result == nullptr)
                printf("none\n");
            else
                printf("%d\n", result->value);
 
            if (!exist) {
                root = erase(root, x);
                if (root != nullptr)
                    root->anc = nullptr;
            }
        }
        if (s == "prev") {
            bool exist = exists(root, x);
            if (!exist)
                root = insert(root, x);
 
            node *result = prev(root, x);
            if (result == nullptr)
                printf("none\n");
            else
                printf("%d\n", result->value);
 
            if (!exist) {
                root = erase(root, x);
                if (root != nullptr)
                    root->anc = nullptr;
            }
        }
 
        // print(root);
        // printf("\n");
 
        scanf("\n");
    }
 
    return 0;
}
