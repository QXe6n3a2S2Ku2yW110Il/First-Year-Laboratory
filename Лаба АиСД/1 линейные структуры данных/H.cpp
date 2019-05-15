#include <iostream>
#include <algorithm>
#include <string>
 
using namespace std;
  
template <typename T>
class ota_vector {
private:
    size_t capacity = 1, size = 0;
    T *a = new T[capacity];
   
    void increase_capacity() {
        T *tmp = new T[capacity * 2];
        for (size_t i = 0; i < capacity; ++i)
            tmp[i] = a[i];
        capacity *= 2;
        swap(a, tmp);
        delete[] tmp;
    }
    void decrease_capacity() {
        capacity /= 2;
        T *tmp = new T[capacity];
        for (size_t i = 0; i < capacity; ++i)
            tmp[i] = a[i];
        swap(a, tmp);
        delete[] tmp;
    }
 
public:
    bool empty() {
        return size <= 0;
    }
    int get_size() {
        return (int)size;
    }
    void push_back(T x) {
        if (capacity <= size)
            increase_capacity();
        a[size++] = x;
    }
    void pop_back() {
        --size;
        if (capacity >= 4 * size && size > 0)
            decrease_capacity();
    }
    T back() {
        return a[size - 1];
    }
    T at(int pos) {
        return a[pos];
    }
    void put(int pos, T x) {
        a[pos] = x;
    }
    void reserve(int x) {
        capacity = (size_t)x;
    }
    ~ota_vector() {
        delete[] a;
        capacity = size = 0;
    }
};
 
template <typename T>
class ota_queue {
private:
    ota_vector<T> left_stack;
    ota_vector<T> right_stack;
 
public:
    void push_back(T x) {
        left_stack.push_back(x);
    }
  
    void pop_front() {
        if (right_stack.empty()) {
            while (!left_stack.empty()) {
                right_stack.push_back(left_stack.back());
                left_stack.pop_back();
            }
        }
        right_stack.pop_back();
    }
 
    T front() {
        if (right_stack.empty()) {
            while (!left_stack.empty()) {
                right_stack.push_back(left_stack.back());
                left_stack.pop_back();
            }
        }
        return right_stack.back();        
    }
};
 
struct treap {
    string key;
    int prior;
    treap *l, *r;
    treap(string &a, int b): key(a), prior(b), l(nullptr), r(nullptr) {}
};
 
pair<treap*, treap*> treap_split(treap *tree, string key) {
    if (tree == nullptr)
        return { nullptr, nullptr };
    if (tree->key < key) {
        auto tmp = treap_split(tree->r, key);
        tree->r = tmp.first;
        return { tree, tmp.second };
    }
    else {
        auto tmp = treap_split(tree->l, key);
        tree->l = tmp.second;
        return { tmp.first, tree };
    }
}
 
treap* treap_merge(treap *L, treap *R) {
    if (L == nullptr)
        return R;
    if (R == nullptr)
        return L;
 
    if (L->prior > R->prior) {
        L->r = treap_merge(L->r, R);
        return L;
    }
    else {
        R->l = treap_merge(L, R->l);
        return R;
    }
}
 
void treap_insert(treap **root, string &new_val, int pos) {
    treap *vertex = new treap(new_val, pos);
    auto one_two = treap_split((*root), vertex->key);
 
    one_two.first = treap_merge(one_two.first, vertex);
    (*root) = treap_merge(one_two.first, one_two.second);
}
 
int treap_search(treap *tree, string &key) {
    if (tree == nullptr)
        return -1;
    if (tree->key == key)
        return tree->prior;
 
    if (tree->key > key)
        return treap_search(tree->l, key);
    return treap_search(tree->r, key);
}
 
void treap_delete(treap **tree) {
    if ((*tree) == nullptr)
        return;
 
    auto l_son = (*tree)->l, r_son = (*tree)->r;
    delete *tree;
 
    treap_delete(&l_son);
    treap_delete(&r_son);
}
 
string int_to_str(int x) {
    string res;
    if (x == 0)
        res = "0";
 
    while (x > 0) {
        res += (char)(x % 10);
        x /= 10;
    }
 
    reverse(res.begin(), res.end());
 
    return res;
}
 
int str_to_int(string &s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); ++i)
        res = res * 10 + s[i] - '0';
 
    return res;
}
 
int get(ota_queue<int> &q) {
    int x = q.front();
    q.pop_front();
 
    return x;
}
 
void update_row(int &curr_row, string &s, int pos, treap *root) {
    string substr_s;
    for (int i = pos; i < (int)s.length(); ++i)
        substr_s += s[i];
 
    curr_row = treap_search(root, substr_s);
}
 
int math_mod(long long x, int mod) {
    return (int)(((x % mod) + mod) % mod);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    const int QUACK_MOD = 65536, CHAR_MOD = 256;
    ota_vector<string> ops;
    treap *label = nullptr;
    string s;
    while (cin >> s) {
        if (s[0] == ':') {
            string curr_label;
            for (int i = 1; i < (int)s.length(); ++i)
                curr_label += s[i];
            treap_insert(&label, curr_label, ops.get_size());
        }
        ops.push_back(s);
    }
    ops.push_back("Q");
 
    ota_queue<int> main_container;
    ota_vector<int> registers;
    for (int i = 'a'; i <= 'z'; ++i)
        registers.push_back(-65537);
    int curr_row = 0, max_row = (int)ops.get_size();
    for (int i = 0; i < 100000 && curr_row < max_row; ++i) {
        auto curr_op = ops.at(curr_row);
        char c = curr_op[0];
        int d = 0, e = 0;
        if (curr_op.length() > 1)
            d = curr_op[1] - 'a';
        if (curr_op.length() > 2)
            e = curr_op[2] - 'a';
 
        if (c == ':') {
            ++curr_row;
            continue;
        }
 
        if ('0' <= c && c <= '9')
            main_container.push_back(str_to_int(curr_op));
 
        else if ('A' <= c && c <= 'Z') {
            if (curr_op.length() == 1) {
                if (c == 'P')
                    cout << get(main_container) << '\n';
                if (c == 'C') {
                    int x = get(main_container);
                    cout << (char)math_mod(x, CHAR_MOD);
                }
                if (c == 'Q')
                    break;
            }
            else {
                if (c == 'P')
                    cout << registers.at(d) << '\n';
                if (c == 'C')
                    cout << (char)math_mod(registers.at(d), CHAR_MOD);
                if (c == 'J')
                    update_row(curr_row, curr_op, 1, label);
                if (c == 'Z') {
                    if (registers.at(d) == 0)
                        update_row(curr_row, curr_op, 2, label);
                }
                if (c == 'E') {
                    if (registers.at(d) == registers.at(e))
                        update_row(curr_row, curr_op, 3, label);
                }
                if (c == 'G') {
                    if (registers.at(d) > registers.at(e))
                        update_row(curr_row, curr_op, 3, label);
                }
            }
        }
 
        else if (c == '>') {
            int x = get(main_container);
            registers.put(d, x);
        }
        else if (c == '<')
            main_container.push_back(registers.at(d));
        else {
            long long x = get(main_container);
            long long y = get(main_container);
 
            if (c == '+')
                main_container.push_back(math_mod(x + y, QUACK_MOD));
            if (c == '-')
                main_container.push_back(math_mod(x - y, QUACK_MOD));
            if (c == '*')
                main_container.push_back(math_mod(x * y, QUACK_MOD));
            if (c == '/') {
                if (x == 0 && y == 0)
                    main_container.push_back(0);
                else
                    main_container.push_back(math_mod(x / y, QUACK_MOD));
            }
            if (c == '%') {
                if (x == 0 && y == 0)
                    main_container.push_back(0);
                else
                    main_container.push_back(math_mod(x % y, QUACK_MOD));
            }
        }
 
        ++curr_row;
    }
 
    treap_delete(&label);
 
    return 0;
}
