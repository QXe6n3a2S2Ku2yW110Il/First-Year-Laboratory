#include <stdio.h>
#include <vector>
 
using namespace std;
 
int main() {
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
 
    const int INF = (int)1e9 + 7;
 
    int n;
    scanf("%d", &n);
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    vector<int> dp(n + 1, INF);
    dp[0] = -INF;
    vector<int> ind(n + 1, -1);
    vector<int> prev(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        int pos = (int) (lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
        dp[pos] = a[i];
        ind[pos] = i;
        prev[i] = ind[pos - 1];
    }
 
    int pos = n;
    vector<int> ans;
    while (dp[pos] == INF)
        --pos;
    pos = ind[pos];
    while (pos > -1) {
        ans.push_back(pos);
        pos = prev[pos];
    }
 
    printf("%d\n", (int)ans.size());
    for (int i = (int)ans.size() - 1; i > -1; --i)
        printf("%d ", a[ans[i]]);
 
    return 0;
}
