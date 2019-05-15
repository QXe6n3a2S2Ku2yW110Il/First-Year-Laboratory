#include <bits/stdc++.h>
 
using namespace std;
 
string toTernary(int x, int n) {
    string res;
    for (int i = 0; i < n; ++i) {
        res += (char)(x % 3 + '0');
        x /= 3;
    }
 
    reverse(res.begin(), res.end());
    return res;
}
 
void writeln(string &s) {
    for (char c : s)
        printf("%c", c);
    printf("\n");
}
 
void shift(string &s) {
    for (int i = 0; i < (int)s.length(); ++i)
        s[i] = (char)((s[i] - '0' + 1) % 3 + '0');
}
 
int main() {
    freopen("antigray.in", "r", stdin);
    freopen("antigray.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    int pow3 = 1;
    for (int i = 0; i < n - 1; ++i)
        pow3 *= 3;
    for (int i = 0; i < pow3; ++i) {
        string curr = "0" + toTernary(i, n - 1);
        for (int j = 0; j < 3; ++j) {
            writeln(curr);
            shift(curr);
        }
    }
 
    return 0;
}
