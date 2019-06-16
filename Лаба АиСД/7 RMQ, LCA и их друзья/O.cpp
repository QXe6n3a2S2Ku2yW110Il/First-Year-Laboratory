#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int LOG2_MAX_N = 18, INF = 1e9 + 7;
 
vector<int> tin, tout;
vector<vector<int>> graph, dp, cost;
 
int timer = 0;
void dfs(int v) {
    tin[v] = timer++;
    for (int u : graph[v])
        dfs(u);
    tout[v] = timer++;
}
 
inline bool ancestor(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}
 
int lca(int v, int u) {
    for (int k = LOG2_MAX_N; k > -1; --k) {
        if (!ancestor(dp[v][k], u))
            v = dp[v][k];
    }
    if (!ancestor(v, u))
        v = dp[v][0];
    return v;
}
 
int minEdge(int v, int u) {
    int res = INF;
    for (int k = LOG2_MAX_N; k > -1; --k) {
        if (!ancestor(dp[v][k], u)) {
            res = min(res, cost[v][k]);
            v = dp[v][k];
        }
    }
    if (!ancestor(v, u))
        res = min(res, cost[v][0]);
    return res;
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    graph.resize(n);
    dp.resize(n, vector<int>(LOG2_MAX_N + 1));
    cost.resize(n, vector<int>(LOG2_MAX_N + 1));
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        graph[--x].push_back(i);
        dp[i][0] = x;
        cost[i][0] = y;
    }
 
    tin.resize(n);
    tout.resize(n);
    dfs(0);
 
    for (int k = 1; k <= LOG2_MAX_N; ++k) {
        for (int i = 0; i < n; ++i) {
            dp[i][k] = dp[dp[i][k - 1]][k - 1];
            cost[i][k] = min(cost[i][k - 1], cost[dp[i][k - 1]][k - 1]);
        }
    }
 
    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        int c = lca(--x, --y);
        printf("%d\n", min(minEdge(x, c), minEdge(y, c)));
    }
 
    return 0;
}
