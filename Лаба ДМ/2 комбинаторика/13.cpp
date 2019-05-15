#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    freopen("num2perm.in", "r", stdin);
    freopen("num2perm.out", "w", stdout);
 
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
 
    vector<long long> fact(19, 1);
    for (int i = 1; i < 19; ++i)
        fact[i] = i * fact[i - 1];
 
    vector<bool> used(n);
    for (int i = 1; i <= n; ++i) {
        long long kLeft = k / fact[n - i];
        k %= fact[n - i];
        int currNum = 0;
        for (int j = 0; j < n; ++j) {
            if (used[j])
                continue;
            if (++currNum == kLeft + 1) {
                printf("%d ", j + 1);
                used[j] = true;
            }
        }
    }
 
    return 0;
}
