#include <bits/stdc++.h>
 
using namespace std;
 
void rec(vector<int> &a, vector<bool> &used, int n) {
    if ((int)a.size() == n) {
        for (int i : a)
            printf("%d ", i);
        printf("\n");
        return;
    }
 
    for (int i = 1; i <= n; ++i) {
        if (used[i])
            continue;
         
        a.push_back(i);
        used[i] = true;
        rec(a, used, n);
        used[i] = false;
        a.pop_back();
    }
}
 
int main() {
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> a;
    vector<bool> used(n + 1, false);
    rec(a, used, n);
 
    return 0;
}
