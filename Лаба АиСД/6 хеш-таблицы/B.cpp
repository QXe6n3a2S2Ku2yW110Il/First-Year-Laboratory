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
 
    int getPos(T key) {
        return search(key);
    }
 
    T get(int pos) {
        return nodes[pos].value;
    }
 
    void pushFront(T key, T value) {
        int pos = getPos(key);
        if (pos > -1) {
            nodes[pos].value = value;
            return;
        }
 
        int newbie = (int) nodes.size();
        nodes.push_back({0, 0, key, value});
 
        nodes[newbie].next = nodes[FICTIVE_HEAD].next;
        nodes[nodes[FICTIVE_HEAD].next].prev = newbie;
        nodes[FICTIVE_HEAD].next = newbie;
        nodes[newbie].prev = FICTIVE_HEAD;
    }
 
    void remove(T key) {
        int pos = search(key);
        if (pos == -1)
            return;
 
        nodes[nodes[pos].next].prev = nodes[pos].prev;
        nodes[nodes[pos].prev].next = nodes[pos].next;
    }
 
 private:
    const int FICTIVE_HEAD = 0;
    int size = 0;
    struct node {
        int next, prev;
        T key, value;
    };
    vector<node> nodes;
 
    int search(T key) {
        int pos = nodes[FICTIVE_HEAD].next;
        while (pos != FICTIVE_HEAD) {
            if (nodes[pos].key == key)
                return pos;
            pos = nodes[pos].next;
        }
 
        return -1;
    }
};
 
int main() {
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    // list<int> table = *(new list<int>[_mod]); <- create on heap (?)
    // list<int> table[_mod]; <- create on stack
    list<string> table[_mod];
    // printf("lists size = %f MByte\n", sizeof(list<int>) * _mod / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
 
    string s;
    while (readString(s)) {
        string key, value, res;
        readString(key);
        int hashCode = getHashCode(key), pos;
 
        switch (s[0]) {
            // put
            case 'p':
                readString(value);
                table[hashCode].pushFront(key, value);
                break;
 
            // get
            case 'g':
                pos = table[hashCode].getPos(key);
                if (pos > -1) {
                    res = table[hashCode].get(pos);
                    writeString(res);
                }
                else
                    printf("none");
                printf("\n");
                break;
 
            // delete
            case 'd':
                table[hashCode].remove(key);
                break;
        }
 
        scanf("\n");
    }
 
    return 0;
}
