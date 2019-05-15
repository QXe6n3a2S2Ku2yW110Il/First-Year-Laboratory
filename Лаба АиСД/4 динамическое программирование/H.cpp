#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
void writeBits(int x) {
    for (int i = 31; i > -1; --i)
        printf("%d", ((x >> i) & 1));
}
 
int main() {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
 
    int n, k;
    long long m;
    scanf("%d%I64d%d", &n, &m, &k);
    // --m;
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());
 
    int pow2n = (1 << n);
    // mask: 1 - exists in perm, n: last element
    // dp[mask][n] - perm qty, last element = n
    vector<vector<long long>> dp(pow2n, vector<long long>(n, 0LL));
    for (int i = 0; i < n; ++i)
        dp[(1 << i)][i] = 1LL;
    for (int mask = 0; mask < pow2n; ++mask) {
        for (int i = 0; i < n; ++i) {
            if (((mask >> i) & 1) == 0)
                continue;
 
            for (int j = 0; j < n; ++j) {
                if (i != j && ((mask >> j) & 1) == 1 && gcd(a[i], a[j]) >= k)
                    dp[mask][i] += dp[(mask ^ (1 << i))][j];
            }
        }
    }
 
    /*for (int mask = 0; mask < pow2n; ++mask) {
        printf("mask = ");
        writeBits(mask);
        printf(":\n");
        for (int i = 0; i < n; ++i)
            printf("[%d] = %d\n", i, dp[mask][i]);
    }*/
 
    vector<int> ans;
    int currMask = pow2n - 1;
    for (int i = 0; i < n; ++i) {
        int pos = 0;
        bool found = false;
        for (; pos < n; ++pos) {
            if (!ans.empty() && gcd(ans.back(), a[pos]) < k)
                continue;
            if (((currMask >> pos) & 1) == 1 && m - dp[currMask][pos] <= 0LL) {
                currMask ^= (1 << pos);
                found = true;
                break;
            }
            m -= dp[currMask][pos];
        }
 
        if (!found) {
            printf("-1");
            return 0;
        }
 
        ans.push_back(a[pos]);
    }
 
    for (int i : ans)
        printf("%d ", i);
 
    return 0;
}
