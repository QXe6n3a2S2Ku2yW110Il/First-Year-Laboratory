#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node(int data, Node* left, Node* right, Node* parent):
        data(data), left(left), right(right), parent(parent) {}
};

class SplayTree {
 private:
    Node* root;

    void rotateLeft(Node* t) {
        Node* b = t->right;
        assert(b);
        kidnapParent(b, t);
        setRightChild(t, b->left);
        setLeftChild(b, t);
    }
    void rotateRight(Node* t) {
        Node* b = t->left;
        assert(b);
        kidnapParent(b, t);
        setLeftChild(t, b->right);
        setRightChild(b, t);
    }
    void splay(Node* x) {
        if (!x) {
            return;
        }
        while (x->parent && x->parent->parent) {
            Node *p = x->parent;
            assert(p);
            Node *q = p->parent;
            assert(q);

            if (q->left == p) {
                if (p->left == x) {
                    rotateRight(q);
                    rotateRight(p);
                } else {
                    rotateLeft(p);
                    rotateRight(q);
                }
            } else {
                if (p->right == x) {
                    rotateLeft(q);
                    rotateLeft(p);
                } else {
                    rotateRight(p);
                    rotateLeft(q);
                }
            }
        }
        if (x->parent) {
            Node* p = x->parent;
            if (p->left == x) {
                rotateRight(p);
            } else {
                rotateLeft(p);
            }
        }
        root = x;
    }

    Node* find(Node* t, int data) {
        if (!t) {
            return nullptr;
        }
        if (t->data == data) {
            return t;
        }
        if (data < t->data) {
            return find(t->left, data);
        }
        return find(t->right, data);
    }
    Node* find(int data) {
        return find(root, data);
    }
    Node* find_max(Node* t, Node* pr = nullptr) {
        if (!t) {
            return pr;
        }
        return find_max(t->right, t);
    }
    Node* find_min(Node* t, Node* pr = nullptr) {
        if (!t) {
            return pr;
        }
        return find_min(t->left, t);
    }
    Node* next(Node* t) {
        if (!t) {
            return t;
        }
        if (t->right) {
            return find_min(t->right);
        } else {
            while (t->parent && t->parent->right == t) {
                t = t->parent;
            }
            return t->parent;
        }
    }
    Node* prev(Node* t) {
        if (!t) {
            return t;
        }
        if (t->left) {
            return find_max(t->left);
        } else {
            while (t->parent && t->parent->left == t) {
                t = t->parent;
            }
            return t->parent;
        }
    }
    Node* find_geq(Node* t, int x) {
        if (!t || x == t->data) {
            return t;
        }
        if (x < t->data) {
            if (!t->left) {
                return t;
            }
            return find_geq(t->left, x);
        } else {
            if (!t->right) {
                return next(t);
            }
            return find_geq(t->right, x);
        }
    }
    void setLeftChild(Node* t, Node* l) {
        if (t) {
            t->left = l;
        }
        if (l) {
            l->parent = t;
        }
    }
    void setRightChild(Node* t, Node* r) {
        t->right = r;
        if (r) {
            r->parent = t;
        }
    }

    void merge(SplayTree s) {
        if (s.root) {
            if (!this->root) {
                this->root = s.root;
                return;
            }
            this->splay(find_max(this->root));
            setRightChild(this->root, s.root);
        }
    }
    void split(SplayTree &l, SplayTree &r, int x) {
        if (!this->root) {
            l = r = SplayTree();
            return;
        }
        Node* v = find_geq(root, x);
        splay(v);
        if (!v) {
            l = SplayTree(root);
            r = SplayTree();
        } else {
            l = SplayTree(root->left);
            root->left = nullptr;
            r = SplayTree(root);
        }
    }

    void _print(Node* t) {
        if (t) {
            _print(t->left);
            cout << t->data << " ";
            _print(t->right);
        }
    }
    void killParent(Node* v) {
        if (v) {
            v->parent = nullptr;
        }
    }
    void kidnapParent(Node* evil, Node* victim) {
        assert(evil);
        assert(victim);
        evil->parent = victim->parent;
        if (victim->parent) {
            if (victim->parent->left == victim) {
                evil->parent->left = evil;
            } else {
                evil->parent->right = evil;
            }
        }
    }

 public:
    SplayTree(Node* root = nullptr): root(root) {
        if (root) {
            root->parent = nullptr;
        }
    }

    bool empty() {
        return !root;
    }

    bool exists(int x) {
        Node* v = find(x);
        splay(v);
        return v;
    }

    Node* next(int x) {
        if (empty()) {
            return nullptr;
        }
        if (x < find_min(root)->data) {
            return find_min(root);
        }
        Node* v = find_geq(root, x);
        splay(v);
        if (v && v->data == x) {
            v = next(v);
        }
        return v;
    }

    Node* prev(int x) {
        if (empty()) {
            return nullptr;
        }
        if (x > find_max(root)->data) {
            return find_max(root);
        }
        Node* v = prev(find_geq(root, x));
        splay(v);
        return v;
    }

    void insert(int x) {
        SplayTree t1, t2;
        // cout << "split("; print(); cout << ", " << x << ") = \n";
        this->split(t1, t2, x);
        // t1.print();
        // t2.print();
        // cout << '\n';


        if (!t2.empty() && t2.root->data == x) {
            root = t2.root;
            setLeftChild(root, t1.root);
        } else {
            root = new Node(x, t1.root, t2.root, nullptr);
            setLeftChild(root, t1.root);
            setRightChild(root, t2.root);
        }
    }

    void remove(int x) {
        Node* v = find(x);
        if (v) {
            splay(v);
            Node* tmp = root->right;
            root = root->left;
            killParent(root);
            merge(SplayTree(tmp));
        }
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string op;
    int x;
    SplayTree st;
    cout << boolalpha;

    while (cin >> op && cin >> x) {
        switch (op[0]) {
            case 'i': {
                st.insert(x);
                break;
            }
            case 'd': {
                st.remove(x);
                break;
            }
            case 'e': {
                cout << st.exists(x) << '\n';
                break;
            }
            case 'n': {
                Node* v = st.next(x);
                if (v) {
                    cout << v->data << '\n';
                } else {
                    cout << "none\n";
                }
                break;
            }
            case 'p': {
                Node* v = st.prev(x);
                if (v) {
                    cout << v->data << '\n';
                } else {
                    cout << "none\n";
                }
                break;
            }
        }
        // st.print();
    }

    return 0;
}
