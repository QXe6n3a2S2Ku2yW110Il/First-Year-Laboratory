#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("mtf.in");
ofstream out("mtf.out");
 
int main() {
    ios_base::sync_with_stdio(false);
    in.tie(NULL);
    out.tie(NULL);
 
    string s;
    in >> s;
 
    vector<char> symb_list('z' - 'a' + 1);
    for (int i = 0; i < 'z' - 'a' + 1; ++i)
        symb_list[i] = (char)(i + 'a');
    for (char c : s) {
        int pos = 0;
        while (pos < (int)s.length()) {
            if (c == symb_list[pos])
                break;
            ++pos;
        }
 
        out << pos + 1 << ' ';
 
        while (pos > 0) {
            swap(symb_list[pos], symb_list[pos - 1]);
            --pos;
        }
    }
 
    return 0;
}
