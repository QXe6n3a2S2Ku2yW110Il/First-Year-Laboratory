#include <stdio.h>
#include <vector>
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
 
    return !s.empty();
}
 
struct node {
    int value;
    node *left, *right, *parent;
};
 
node *root;
 
void insert(int x) {
    node *tree = root;
    node *newbie = new node;
    newbie->right = newbie->left = newbie->parent = nullptr;
    newbie->value = x;
 
    if (root == nullptr) {
        root = newbie;
        return;
    }
 
    while (true) {
        if (x == tree->value) {
            delete newbie;
            return;
        }
 
        if (x > tree->value) {
            if (tree->right == nullptr) {
                tree->right = newbie;
                newbie->parent = tree;
                return;
            }
            tree = tree->right;
        } else {
            if (tree->left == nullptr) {
                tree->left = newbie;
                newbie->parent = tree;
                return;
            }
            tree = tree->left;
        }
    }
}
 
node* erase(node *tree, int x) {
    if (tree == nullptr)
        return tree;
 
    if (x < tree->value) {
        tree->left = erase(tree->left, x);
        if (tree->left != nullptr)
            tree->left->parent = tree;
    } else if (x > tree->value) {
        tree->right = erase(tree->right, x);
        if (tree->left != nullptr)
            tree->left->parent = tree;
    } else {
        if (tree->left != nullptr && tree->right != nullptr) {
            node *tmp = tree->right;
            while (tmp->left != nullptr)
                tmp = tmp->left;
            tree->value = tmp->value;
            tree->right = erase(tree->right, tree->value);
        } else if (tree->left != nullptr) {
            node *tmp = tree->left;
            if (tmp != nullptr)
                tmp->parent = tree->parent;
            delete tree;
            tree = tmp;
        } else {
            node *tmp = tree->right;
            if (tmp != nullptr)
                tmp->parent = tree->parent;
            delete tree;
            tree = tmp;
        }
    }
 
    return tree;
}
 
node* search(int x) {
    node *tree = root;
    while (tree != nullptr && tree->value != x) {
        if (x > tree->value)
            tree = tree->right;
        else
            tree = tree->left;
    }
 
    return tree;
}
 
node* next(int x) {
    node *tree = search(x);
    if (tree->right == nullptr) {
        node *p = tree->parent;
        while (p != nullptr && tree == p->right) {
            tree = p;
            p = p->parent;
        }
        return p;
    } else {
        tree = tree->right;
        while (tree->left != nullptr)
            tree = tree->left;
        return tree;
    }
}
 
node* prev(int x) {
    node *tree = search(x);
    if (tree->left == nullptr) {
        node *p = tree->parent;
        while (p != nullptr && tree == p->left) {
            tree = p;
            p = p->parent;
        }
        return p;
    } else {
        tree = tree->left;
        while (tree->right != nullptr) {
            tree = tree->right;
        }
        return tree;
    }
}
 
int main() {
    string s;
    while (readString(s)) {
        int x;
        scanf("%d", &x);
 
        if (s == "insert")
            insert(x);
        if (s == "delete")
            root = erase(root, x);
        if (s == "exists")
            printf((search(x) == nullptr ? "false\n" : "true\n"));
        if (s == "next") {
            bool exist = search(x);
            if (!exist)
                insert(x);
 
            node *res = next(x);
            if (res == nullptr)
                printf("none\n");
            else
                printf("%d\n", res->value);
 
            if (!exist)
                root = erase(root, x);
        }
        if (s == "prev") {
            bool exist = search(x);
            if (!exist)
                insert(x);
 
            node *res = prev(x);
            if (res == nullptr)
                printf("none\n");
            else
                printf("%d\n", res->value);
 
            if (!exist)
                root = erase(root, x);
        }
 
        scanf("\n");
    }
 
    return 0;
}
