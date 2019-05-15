#include <bits/stdc++.h>
 
using namespace std;
 
void rec(vector<int> &a, int n, int k, int prev = 0) {
    if ((int)a.size() == k) {
        for (int i : a)
            printf("%d ", i);
        printf("\n");
        return;
    }
 
    for (int i = prev + 1; i <= n; ++i) {
        a.push_back(i);
        rec(a, n, k, i);
        a.pop_back();
    }
}
 
int main() {
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);
 
    int n, k;
    scanf("%d%d", &n, &k);
 
    vector<int> a;
    vector<bool> used(n + 1, false);
    rec(a, n, k);
 
    return 0;
}
