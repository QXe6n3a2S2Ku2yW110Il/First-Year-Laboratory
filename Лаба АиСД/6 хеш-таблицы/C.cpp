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
 
struct node {
    string key, value;
    node *next, *nextNode, *prevNode;
};
 
node *table[_mod];
node *last;
 
node* search(string &key) {
    auto list = table[getHashCode(key)];
    while (list != nullptr && list->key != key)
        list = list->next;
 
    return list;
}
 
node* next(string &key) {
    auto list = search(key);
    return (list == nullptr ? nullptr : list->nextNode);
}
 
node* prev(string &key) {
    auto list = search(key);
    return (list == nullptr ? nullptr : list->prevNode);
}
 
void pushBack(string &key, string &value) {
    int hashCode = getHashCode(key);
    auto list = table[hashCode];
    if (list != nullptr) {
        while (list->next != nullptr && list->key != key)
            list = list->next;
 
        if (list->key == key) {
            list->value = value;
            return;
        }
        // auto newbie = new node({key, value, nullptr, nullptr, nullptr, nullptr});
        // newbir->next = table[hashCode];
        // list = table[hashCode] = table[hashCode]->prev = newbie;
        // assert list->next == nullptr;
        list = list->next = new node({key, value, nullptr, nullptr, nullptr});
    }
    else
        list = table[hashCode] = new node({key, value, nullptr, nullptr, nullptr});
 
    if (last != nullptr) {
        last->nextNode = list;
        list->prevNode = last;
    }
    last = list;
}
 
void remove(string &key) {
    int hashCode = getHashCode(key);
    auto list = table[hashCode];
    node *prev = nullptr;
    while (list != nullptr && list->key != key) {
        prev = list;
        list = list->next;
    }
 
    if (list == nullptr)
        return;
 
    if (prev != nullptr)
        prev->next = list->next;
    else
        table[hashCode] = list->next;
 
    if (last == list) {
        last = list->prevNode;
        if (last != nullptr)
            last->nextNode = nullptr;
    } else {
        if (list->prevNode != nullptr)
            list->prevNode->nextNode = list->nextNode;
        if (list->nextNode != nullptr)
            list->nextNode->prevNode = list->prevNode;
    }
 
    delete list;
}
 
void writeNode(node *x) {
    if (x == nullptr)
        printf("none");
    else
        writeString(x->value);
    printf("\n");
}
 
int main() {
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    // list<int> table = *(new list<int>[_mod]); <- create on heap (?)
    // list<int> table[_mod]; <- create on stack
    // printf("lists size = %f MByte\n", sizeof(list<int>) * _mod / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
    // printf("table size = %f MByte\n", sizeof(table) / 1024.0 / 1024);
 
    string s;
    while (readString(s)) {
        string key, value;
        node *res;
        readString(key);
 
        switch (s[0]) {
            // put
            case 'p':
                if (s.length() == 3) {
                    readString(value);
                    pushBack(key, value);
                } else {
                    res = prev(key);
                    writeNode(res);
                }
                break;
 
            // get
            case 'g':
                res = search(key);
                writeNode(res);
                break;
 
            // delete
            case 'd':
                remove(key);
                break;
 
            // next
            case 'n':
                res = next(key);
                writeNode(res);
                break;
        }
 
        scanf("\n");
    }
 
    return 0;
}
