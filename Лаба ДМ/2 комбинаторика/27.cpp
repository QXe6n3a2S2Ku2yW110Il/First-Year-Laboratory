#include <bits/stdc++.h>
 
using namespace std;
 
void readString(string &s) {
    char c;
    while (scanf(" \n%c", &c) == 1)
        s += c;
}
 
void nextBrackets(string &s) {
    int cnt = 0, pos;
    for (pos = (int)s.length() - 1; pos > 0; --pos) {
        if (s[pos] == '(') {
            if (++cnt < 0)
                break;
        }
        else
            --cnt;
    }
 
    if (pos == 0) {
        printf("-");
        exit(0);
    }
 
    int open = 0, brackets = 0;
    for (int i = 0; i < pos; ++i) {
        printf("%c", s[i]);
        if (s[i] == '(')
            ++open;
        ++brackets;
    }
    printf(")");
    ++brackets;
    for (int i = 0; i < (int)s.length() / 2 - open; ++i) {
        printf("(");
        ++brackets;
    }
    for (int i = brackets; i < (int)s.length(); ++i)
        printf(")");
}
 
int main() {
    freopen("nextbrackets.in", "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
 
    string s;
    readString(s);
    nextBrackets(s);
 
    return 0;
}
