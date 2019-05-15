#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
struct dpType {
    int a = 0, b = 0;
 
    dpType() = default;
    dpType(int x, int y): a(x), b(y) {}
};
 
string a, b;
int n, m;
 
void readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            return;
        s += c;
    }
}
 
void writeString(string &s) {
    for (char c : s)
        printf("%c", c);
}
 
string check(string &sa, int aLeft,
             string &sb, int bLeft, int bRight) {
    for (int i = bLeft; i <= bRight; ++i) {
        if (sa[aLeft - 1] == sb[i - 1]) {
            string tmp = "";
            tmp += sa[aLeft - 1];
            return tmp;
        }
    }
    return "";
}
 
string rec(int aLeft, int aRight, int bLeft, int bRight) {
    if (aLeft == aRight)
        return check(a, aLeft, b, bLeft, bRight);
 
    if (bLeft == bRight)
        return check(b, bLeft, a, aLeft, aRight);
 
    int aMiddle = (aRight + aLeft) / 2;
    vector<dpType> dpa(m + 2, dpType());
    for (int i = aLeft; i <= aMiddle; ++i) {
        dpa[0].b = 0;
        for (int j = bLeft; j <= bRight; ++j) {
            dpa[j].a = dpa[j].b;
            if (a[i - 1] == b[j - 1]) {
                dpa[j].b = dpa[j - 1].a + 1;
            } else {
                if (dpa[j - 1].b > dpa[j].a)
                    dpa[j].b = dpa[j - 1].b;
                else
                    dpa[j].b = dpa[j].a;
            }
        }
    }
 
    vector<dpType> dpb(m + 2, dpType());
    for (int i = aRight; i > aMiddle; --i) {
        dpb[0].b = 0;
        for (int j = bRight; j >= bLeft; --j) {
            dpb[j].a = dpb[j].b;
            if (a[i - 1] == b[j - 1]) {
                dpb[j].b = dpb[j + 1].a + 1;
            } else {
                if (dpb[j + 1].b > dpb[j].a)
                    dpb[j].b = dpb[j + 1].b;
                else
                    dpb[j].b = dpb[j].a;
            }
        }
    }
 
    int currMax = -810, pos = -1;
    for (int i = bLeft - 1; i <= bRight; ++i) {
        if (currMax <= dpa[i].b + dpb[i + 1].b) {
            currMax = dpa[i].b + dpb[i + 1].b;
            pos = i;
        }
    }
 
    return rec(aLeft, aMiddle, bLeft, pos) + rec(aMiddle + 1, aRight, pos + 1, bRight);
}
 
int main() {
    // freopen("optimalcode.in", "r", stdin);
    // freopen("optimalcode.out", "w", stdout);
 
    readString(a);
    readString(b);
 
    n = (int)a.length(), m = (int)b.length();
    string ans = rec(1, n, 1, m);
    writeString(ans);
 
    return 0;
}
