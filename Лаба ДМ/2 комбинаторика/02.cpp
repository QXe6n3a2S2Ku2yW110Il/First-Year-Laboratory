#include <bits/stdc++.h>
 
using namespace std;
 
void grayCode(vector<string> &a) {
    int n = (int)a.size();
    vector<string> res = a;
    for (int i = n - 1; i > -1; --i)
        res.push_back(a[i]);
     
    for (int i = 0; i < n; ++i)
        res[i] += '0';
    for (int i = n; i < 2 * n; ++i)
        res[i] += '1';
     
    swap(a, res);
}
 
void writeln(string &s) {
    for (int i = (int)s.length() - 1; i > -1; --i)
        printf("%c", s[i]);
    printf("\n");
}
 
int main() {
    freopen("gray.in", "r", stdin);
    freopen("gray.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<string> gr(2);
    gr[0] = "0";
    gr[1] = "1";
    for (int i = 1; i < n; ++i)
        grayCode(gr);
     
    for (auto &i : gr)
        writeln(i);
 
    return 0;
}
