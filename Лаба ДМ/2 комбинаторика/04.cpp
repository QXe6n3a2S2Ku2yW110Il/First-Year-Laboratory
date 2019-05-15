#include <bits/stdc++.h>
 
using namespace std;
 
void writeln(string &s) {
    for (char c : s)
        printf("%c", c);
    printf("\n");
}
 
void chainCode(int n) {
    string curr;
    for (int i = 0; i < n; ++i)
        curr += '0';
    set<string> used;
    while (true) {
        string pref;
        pref.assign(curr.begin() + 1, curr.end());
        string one = pref + '1', zero = pref + '0';
 
        if (!used.count(one))
            curr = one;
        else if (!used.count(zero))
            curr = zero;
        else
            break;
         
        writeln(curr);
        used.insert(curr);
    }
}
 
int main() {
    freopen("chaincode.in", "r", stdin);
    freopen("chaincode.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    chainCode(n);
 
    return 0;
}
