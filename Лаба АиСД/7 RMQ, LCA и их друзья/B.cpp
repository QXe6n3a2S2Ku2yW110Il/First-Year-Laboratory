#include <stdio.h>
#include <vector>
 
using namespace std;
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    vector<int> log2(n + 1);
    log2[1] = 0;
    for (int i = 2; i <= n; ++i)
        log2[i] = log2[i / 2] + 1;
 
    vector<int> arr(n);
    scanf("%d", &arr[0]);
    for (int i = 1; i < n; ++i)
        arr[i] = (int) ((23LL * arr[i - 1] + 21563) % 16714589);
 
    int log2n = log2[n];
    vector<vector<int>> st(n, vector<int>(log2n + 1));
    for (int i = 0; i < n; ++i)
        st[i][0] = arr[i];
    for (int j = 1; j <= log2n; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
 
    int u, v, ans = 0;
    scanf("%d%d", &u, &v);
    for (int i = 1; i <= m; ++i) {
        int left = min(u, v) - 1, right = max(u, v) - 1;
        int log2len = log2[right - left + 1];
        ans = min(st[left][log2len], st[right - (1 << log2len) + 1][log2len]);
 
        if (i == m)
            continue;
        u = (int) ((17LL * u + 751 + ans + 2 * i) % n) + 1;
        v = (int) ((13LL * v + 593 + ans + 5 * i) % n) + 1;
    }
 
    printf("%d %d %d", u, v, ans);
 
    return 0;
}
