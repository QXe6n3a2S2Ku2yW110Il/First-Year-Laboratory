#include <bits/stdc++.h>
 
using namespace std;
 
int n, m;
vector<vector<vector<int>>> s = {{{1}}};
void rec(int x) {
    if (x >= n + 1)
        return;
 
    vector<vector<vector<int>>> c;
    for (auto &i : s) {
        for (auto &j : i) {
            j.push_back(x);
            c.push_back(i);
            j.pop_back();
        }
        vector<vector<int>> cpy = i;
        cpy.push_back({x});
        c.push_back(cpy);
    }
 
    swap(c, s);
    rec(x + 1);
}
 
int main() {
    freopen("part2sets.in", "r", stdin);
    freopen("part2sets.out", "w", stdout);
 
    scanf("%d%d", &n, &m);
    rec(2);
 
    for (auto &i : s) {
        if ((int)i.size() != m)
            continue;
        for (auto &j : i) {
            for (int k : j)
                printf("%d ", k);
            printf("\n");
        }
        printf("\n");
    }
 
    return 0;
}
