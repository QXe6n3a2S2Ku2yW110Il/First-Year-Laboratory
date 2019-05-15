#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("lzw.in");
ofstream out("lzw.out");
 
int main() {
    ios_base::sync_with_stdio(false);
    in.tie(NULL);
    out.tie(NULL);
 
    map<string, int> dict;
    for (char c = 'a'; c <= 'z'; ++c) {
        string t = "";
        t += c;
        dict[t] = c - 'a' + 1;
    }
 
    string s, curr;
    in >> s;
    for (int i = 0; i < (int)s.length(); ++i) {
            curr += s[i];
         
        if (dict[curr] == 0) {
            dict[curr] = (int)dict.size();
            curr.pop_back();
            out << dict[curr] - 1 << ' ';
 
            curr = "";
            --i;
        }
    }
    if (!curr.empty())
        out << dict[curr] - 1;
 
    return 0;
}
