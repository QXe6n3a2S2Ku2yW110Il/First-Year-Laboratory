#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
bool readString(string &s) {
    s = "";
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
 
    return !s.empty();
}
 
void writeString(string &s) {
    for (char c : s)
        printf("%c", c);
}
 
const int _a = 4561, _c = 51349, _mod = 243000;
int getHashCode(string &s) {
    int res = 0, p = 1;
    for (char c : s) {
        res = (res + (c * p) % _mod) % _mod;
        p = (p * 31) % _mod;
    }
    return res;
}
 
template <typename T>
class list {
 public:
    list() {
        nodes.resize(1);
    }
 
    vector<T> getAll(T key) {
        int pos = nodes[FICTIVE_HEAD].next;
        vector<T> res;
        while (pos != FICTIVE_HEAD) {
            if (nodes[pos].key == key)
                res.push_back(nodes[pos].value);
            pos = nodes[pos].next;
        }
 
        return res;
    }
 
    T get(int pos) {
        return nodes[pos].value;
    }
 
    void pushFront(T key, T value) {
        int newbie = (int) nodes.size();
        nodes.push_back({0, 0, key, value});
 
        nodes[newbie].next = nodes[FICTIVE_HEAD].next;
        nodes[nodes[FICTIVE_HEAD].next].prev = newbie;
        nodes[FICTIVE_HEAD].next = newbie;
        nodes[newbie].prev = FICTIVE_HEAD;
    }
 
    void remove(T key, T value) {
        vector<int> allPos = search(key, value);
        for (int pos : allPos) {
            nodes[nodes[pos].next].prev = nodes[pos].prev;
            nodes[nodes[pos].prev].next = nodes[pos].next;
        }
    }
 
    void removeAll(T key) {
        vector<int> allPos = searchAll(key);
        for (int i : allPos) {
            nodes[nodes[i].next].prev = nodes[i].prev;
            nodes[nodes[i].prev].next = nodes[i].next;
        }
    }
 
 private:
    const int FICTIVE_HEAD = 0;
    int size = 0;
    struct node {
        int next, prev;
        T key, value;
    };
    vector<node> nodes;
 
    vector<int> searchAll(T key) {
        int pos = nodes[FICTIVE_HEAD].next;
        vector<int> res;
        while (pos != FICTIVE_HEAD) {
            if (nodes[pos].key == key)
                res.push_back(pos);
            pos = nodes[pos].next;
        }
 
        return res;
    }
 
    vector<int> search(T key, T value) {
        int pos = nodes[FICTIVE_HEAD].next;
        vector<int> res;
        while (pos != FICTIVE_HEAD) {
            if (nodes[pos].key == key && nodes[pos].value == value)
                res.push_back(pos);
            pos = nodes[pos].next;
        }
 
        return res;
    }
};
 
int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    // list<int> table = *(new list<int>[_mod]); <- create on heap (?)
    // list<int> table[_mod]; <- create on stack
    list<string> table[_mod];
    // printf("lists size = %f MByte\n", sizeof(list<int>) * _mod / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
 
    string s;
    while (readString(s)) {
        string key, value;
        readString(key);
        int hashCode = getHashCode(key);
        vector<string> res;
 
        switch (s[0]) {
            // put
            case 'p':
                readString(value);
                table[hashCode].pushFront(key, value);
                break;
 
            // get
            case 'g':
                res = table[hashCode].getAll(key);
                printf("%d", (int) res.size());
                for (auto &i : res) {
                    printf(" ");
                    writeString(i);
                }
                printf("\n");
                break;
 
            // delete
            case 'd':
                if (s.length() > 6) {
                    table[hashCode].removeAll(key);
                } else {
                    readString(value);
                    table[hashCode].remove(key, value);
                }
                break;
        }
 
        scanf("\n");
    }
 
    return 0;
}
