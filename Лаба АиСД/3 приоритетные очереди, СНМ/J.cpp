#include <bits/stdc++.h>

using namespace std;

vector<int> treeKey(1);

template <typename T>
struct binomialTree {
    int num = -1, degree = -1;
    binomialTree *parent, *child, *sibling;

    /*bool operator < (const binomialTree *b) const {
        if (treeKey[num] == treeKey[b->num]) {
            return num < b->num;
        }
        return treeKey[num] < treeKey[b->num];
    }*/

    binomialTree() = default;

    binomialTree(int shym) : num(shym), degree(1),
                            parent(nullptr), child(nullptr), sibling(nullptr) {}
};

template <typename T>
struct binomialHeap;
vector<binomialTree<int>*> num2tree(1);
vector<binomialHeap<int>*> num2heap(1);
vector<binomialHeap<int>*> heaps;

// bool operator < don't want to work
bool compare(int a, int b) {
    if (treeKey[a] == treeKey[b]) {
        return a < b;
    }
    return treeKey[a] < treeKey[b];
}

template <typename T>
binomialTree<T>* mergeEqualTree(binomialTree<T> *a, binomialTree<T> *b) {
    // if (b < a)
    if (compare(b->num, a->num))
        swap(a, b);
    
    b->sibling = a->child;
    a->child = b;
    b->parent = a;
    ++a->degree;
    
    return a;
}

template <typename T>
struct binomialHeap {
    binomialTree<T> *head = new binomialTree<T>();
    vector<binomialTree<T>*> roots;

    binomialHeap() = default;

    binomialHeap(binomialTree<T> *t) {
        head = t;
        roots = {t};
        num2heap[t->num] = this;
    }

    void updateHeap() {
        for (binomialTree<T> *t : this->roots) {
            num2heap[t->num] = this;
            t->parent = nullptr;
        }
    }

    binomialTree<T> *extractMin() {
        if (roots.empty()) {
            printf("Pomelo");
            exit(0);
        }

        binomialTree<T> *res = roots[0];
        for (binomialTree<T> *t : roots) {
            // t = min(t, res);
            if (compare(t->num, res->num))
                res = t;
        }
        return res;
    }
};

template <typename T>
binomialHeap<T>* mergeHeaps(binomialHeap<T> *a, binomialHeap<T> *b) {
    auto *res = new binomialHeap<T>;
    auto aCurr = a->roots.begin(), aNull = a->roots.end();
    auto bCurr = b->roots.begin(), bNull = b->roots.end();
    binomialTree<T> *tmp = nullptr;

    while (aCurr != aNull || bCurr != bNull) {
        if (aCurr != aNull && bCurr != bNull) {
            if ((*bCurr)->degree == (*aCurr)->degree) {
                if (tmp == nullptr) {
                    tmp = mergeEqualTree(*aCurr, *bCurr);
                    ++aCurr;
                    ++bCurr;
                    continue;
                }
                if (tmp->degree < (*aCurr)->degree) {
                    res->roots.push_back(tmp);
                    tmp = nullptr;
                    continue;
                }
                if (tmp->degree == (*aCurr)->degree) {
                    res->roots.push_back(tmp);
                    tmp = nullptr;
                    continue;
                }
                
                printf("Pomelo");
                exit(0);
            }
            if ((*bCurr)->degree < (*aCurr)->degree) {
                swap(aCurr, bCurr);
                swap(aNull, bNull);
            }
        }
        if (bCurr == bNull) {
            if (tmp == nullptr) {
                res->roots.push_back(*aCurr);
                ++aCurr;
                continue;
            }
            if (tmp->degree < (*aCurr)->degree) {
                res->roots.push_back(tmp);
                tmp = nullptr;
                continue;
            }
            if (tmp->degree > (*aCurr)->degree) {
                res->roots.push_back(*aCurr);
                ++aCurr;
                continue;
            }
            if (tmp->degree == (*aCurr)->degree) {
                tmp = mergeEqualTree(tmp, *aCurr);
                ++aCurr;
                continue;
            }
        } else {
            if (tmp == nullptr) {
                res->roots.push_back(*bCurr);
                ++bCurr;
                continue;
            }
            if (tmp->degree < (*bCurr)->degree) {
                res->roots.push_back(tmp);
                tmp = nullptr;
                continue;
            }
            if (tmp->degree > (*bCurr)->degree) {
                res->roots.push_back(*bCurr);
                ++bCurr;
                continue;
            }
            if (tmp->degree == (*bCurr)->degree) {
                tmp = mergeEqualTree(tmp, *bCurr);
                ++bCurr;
                continue;
            }
        }
    }
    if (tmp != nullptr) {
        res->roots.push_back(tmp);
    }

    res->updateHeap();
    return res;
}

template <typename T>
binomialHeap<T>* erase(binomialTree<T> *tree) {
    binomialHeap<T> *heap = num2heap[tree->num];
    while (tree->parent != nullptr) {
        swap(tree->num, tree->parent->num);
        num2tree[tree->num] = tree;
        heap = num2heap[tree->num];
        tree = tree->parent;
    }

    auto res = new binomialHeap<T>;
    for (auto *bros = tree->child; bros != nullptr; bros = bros->sibling)
        res->roots.push_back(bros);
    reverse(res->roots.begin(), res->roots.end());
    res->updateHeap();

    auto delPos = find(heap->roots.begin(), heap->roots.end(), tree);
    heap->roots.erase(delPos);
    *heap = *mergeHeaps(heap, res);

    heap->updateHeap();
    return heap;
}

template <typename T>
void insert(int num, int val, int inserted) {
    treeKey.push_back(val);
    num2heap.push_back(heaps[num]);
    num2tree.push_back(new binomialTree<T>(inserted));

    auto *res = new binomialHeap<T>(num2tree.back());
    heaps[num] = mergeHeaps(heaps[num], res);
    heaps[num]->updateHeap();
}

template <typename T>
void eat(int a, int b) {
    heaps[a] = mergeHeaps(heaps[a], heaps[b]);
    heaps[a]->updateHeap();
    heaps[b] = new binomialHeap<T>;
}

template <typename T>
void changeKey(int num, int val) {
    binomialHeap<T> *tmp = erase(num2tree[num]);
    treeKey[num] = val;

    num2tree[num] = new binomialTree<T>(num);
    auto *res = new binomialHeap<T>(num2tree[num]);

    *tmp = *mergeHeaps(tmp, res);
    tmp->updateHeap();
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    heaps.resize(n + 1);
    for (int i = 0; i < n + 1; ++i)
        heaps[i] = new binomialHeap<int>();

    int elements = 0;
    for (int i = 0; i < m; ++i) {
        // printf("i = %d:\n", i);
        int type;
        scanf("%d", &type);

        if (type == 0) {
            int val, num;
            scanf("%d%d", &num, &val);

            insert<int>(num, val, ++elements);
        }
        if (type == 1) {
            int a, b;
            scanf("%d%d", &a, &b);

            eat<int>(b, a);
        }
        if (type == 2) {
            int num;
            scanf("%d", &num);

            erase(num2tree[num]);
        }
        if (type == 3) {
            int num, val;
            scanf("%d%d", &num, &val);

            changeKey<int>(num, val);
        }
        if (type == 4) {
            int num;
            scanf("%d", &num);

            printf("%d\n", treeKey[heaps[num]->extractMin()->num]);
        }
        if (type == 5) {
            int num;
            scanf("%d", &num);

            erase(heaps[num]->extractMin());
        }
    }

    return 0;
}
