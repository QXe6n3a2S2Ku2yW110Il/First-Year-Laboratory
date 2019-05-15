#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int INF = (int)1e9 + (int)9e8;
 
int n;
vector<vector<int>> dp, graph;
 
int rec(int v, int mask) {
    if (dp[v][mask] < INF)
        return dp[v][mask];
 
    for (int u = 0; u < n; ++u) {
        if (graph[v][u] > -1 && ((mask >> u) & 1) == 1)
            dp[v][mask] = min(dp[v][mask], rec(u, (mask ^ (1 << u))) + graph[v][u]);
    }
 
    return dp[v][mask];
}
 
int main() {
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
 
    int m;
    scanf("%d%d", &n, &m);
 
    graph.resize(n, vector<int>(n, -1));
    while (m--) {
        int from, to, cost;
        scanf("%d%d%d", &from, &to, &cost);
 
        graph[--from][--to] = cost;
        graph[to][from] = cost;
    }
 
    dp.resize(n, vector<int>((1 << n), INF));
    for (int v = 0; v < n; ++v)
        dp[v][0] = 0;
 
    int ans = INF;
    for (int v = 0; v < n; ++v)
        ans = min(ans, rec(v, (1 << n) - 1 - (1 << v)));
 
    printf("%d", (ans == INF) ? -1 : ans);
 
    return 0;
}
