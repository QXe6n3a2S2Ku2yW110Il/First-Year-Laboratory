#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("perm2num.in", "r", stdin);
    freopen("perm2num.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<long long> fact(19, 1);
    for (int i = 1; i < 19; ++i)
        fact[i] = i * fact[i - 1];
     
    long long ans = 0;
    vector<bool> used(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
 
        for (int j = 1; j < x; ++j) {
            if (used[j])
                continue;
             
            ans += fact[n - i];
        }
        used[x] = true;
    }
 
    printf("%lld", ans);
 
    return 0;
}
