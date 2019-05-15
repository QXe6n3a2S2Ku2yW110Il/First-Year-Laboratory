#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("nextvector.in", "r", stdin);
    freopen("nextvector.out", "w", stdout);
 
    string s;
    char c;
    bool zero = true, one = true;
    while (scanf(" \n%c", &c) == 1) {
        if (c == '0')
            one = false;
        if (c == '1')
            zero = false;
        s += c;
    }
 
    if (zero)
        printf("-");
    else {
        int pos = 0;
        for (int i = (int)s.length() - 1; i > -1; --i) {
            if (s[i] == '1') {
                pos = i;
                break;
            }
        }
 
        for (int i = 0; i < pos; ++i)
            printf("%c", s[i]);
        printf("0");
        for (int i = pos + 1; i < (int)s.length(); ++i)
            printf("1");
    }
    printf("\n");
 
    if (one)
        printf("-");
    else {
        int pos = 0;
        for (int i = (int)s.length() - 1; i > -1; --i) {
            if (s[i] == '0') {
                pos = i;
                break;
            }
        }
 
        for (int i = 0; i < pos; ++i)
            printf("%c", s[i]);
        printf("1");
        for (int i = pos + 1; i < (int)s.length(); ++i)
            printf("0");
    }
 
    return 0;
}
