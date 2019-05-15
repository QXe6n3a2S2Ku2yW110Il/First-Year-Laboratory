#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("bwt.in");
ofstream out("bwt.out");
 
int main() {
    ios_base::sync_with_stdio(false);
    in.tie(NULL);
    out.tie(NULL);
 
    string s;
    in >> s;
 
    int n = (int)s.length();
    vector<string> arrs;
    for (int i = 0; i < n; ++i) {
        arrs.push_back(s);
         
        char back_symbol = s.back();
        s.pop_back();
        s = back_symbol + s;
    }
    sort(arrs.begin(), arrs.end());
 
    for (int i = 0; i < n; ++i)
        out << arrs[i].back();
 
    return 0;
}
