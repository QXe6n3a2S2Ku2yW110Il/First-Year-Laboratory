#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
bool readString(string &s) {
    s = "";
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ')
            break;
        s += c;
    }
 
    return !s.empty();
}
 
const int _a = 4561, _c = 51349, _mod = 243000;
int getHashCode(int seed) {
    return ((seed * _a + _c) % _mod + _mod) % _mod;
}
 
template <typename T>
class list {
 public:
    list() {
        values.resize(1);
    }
 
    bool exists(T value) {
        return search(value) > -1;
    }
 
    void pushFront(T value) {
        if (exists(value))
            return;
 
        int newbie = (int) values.size();
        values.push_back({0, 0, value});
 
        values[newbie].next = values[FICTIVE_HEAD].next;
        values[values[FICTIVE_HEAD].next].prev = newbie;
        values[FICTIVE_HEAD].next = newbie;
        values[newbie].prev = FICTIVE_HEAD;
    }
 
    void remove(T value) {
        int pos = search(value);
        if (pos == -1)
            return;
 
        values[values[pos].next].prev = values[pos].prev;
        values[values[pos].prev].next = values[pos].next;
    }
 
 private:
    const int FICTIVE_HEAD = 0;
    int size = 0;
    struct node {
        int next, prev;
        T value;
    };
    vector<node> values;
 
    int search(T value) {
        int pos = values[FICTIVE_HEAD].next;
        while (pos != FICTIVE_HEAD) {
            if (values[pos].value == value)
                return pos;
            pos = values[pos].next;
        }
 
        return -1;
    }
};
 
int main() {
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    // list<int> table = *(new list<int>[_mod]); <- create on heap (?)
    // list<int> table[_mod]; <- create on stack
    list<int> table[_mod];
    // printf("lists size = %f MByte\n", sizeof(list<int>) * _mod / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
 
    string s;
    while (readString(s)) {
        int x;
        scanf("%d", &x);
        int hashCode = getHashCode(x);
 
        switch (s[0]) {
            // insert
            case 'i':
                // printf("insert\n");
                table[hashCode].pushFront(x);
                break;
 
            // exists
            case 'e':
                // printf("exists\n");
                printf(table[hashCode].exists(x) ? "true\n" : "false\n");
                break;
 
            // delete
            case 'd':
                // printf("delete\n");
                table[hashCode].remove(x);
                break;
        }
 
        scanf("\n");
    }
 
    return 0;
}
