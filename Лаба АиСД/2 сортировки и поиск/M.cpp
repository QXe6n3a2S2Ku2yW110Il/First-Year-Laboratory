#include <bits/stdc++.h>
 
using namespace std;
 
void check(int x, int n, vector<vector<pair<int, int>>> &comps) {
    vector<int> bits(n);
    for (int i = 0; i < n; ++i)
        bits[i] = ((x >> i) & 1);
 
    for (int i = 0; i < (int)comps.size(); ++i) {
        for (auto j : comps[i]) {
            if (bits[j.first] > bits[j.second])
                swap(bits[j.first], bits[j.second]);
        }
    }
 
    int pos = 0;
    while (pos < n && bits[pos] == 0)
        ++pos;
    while (pos < n && bits[pos] == 1)
        ++pos;
 
    if (pos != n) {
        printf("No");
        exit(0);
    }
}
 
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
 
    vector<vector<pair<int, int>>> comps(k);
    for (int i = 0; i < k; ++i) {
        int r;
        scanf("%d", &r);
        while (r--) {
            int x, y;
            scanf("%d%d", &x, &y);
            comps[i].push_back({min(x, y) - 1, max(x, y) - 1});
        }
    }
 
    for (int i = 0; i <= (1 << n); ++i)
        check(i, n, comps);
 
    printf("Yes");
 
    return 0;
}
