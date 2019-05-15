#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct edge {
    int to = 0, w = 0;
 
    edge() = default;
    edge(int a, int b): to(a), w(b) {}
};
 
// dp1[i] - max matching in subtree i, i connected with vertex in matcing
// dp2[i] - max matching in subtree i, i disconnected with vertex in matcing
// dp[i] = max(dp1[i], dp2[1])
vector<long long> dp, dp1, dp2;
vector<vector<edge>> graph;
void dfs(int v, int p = -1) {
    if (graph[v].size() == 1 && graph[v][0].to == p) {
        dp[v] = dp1[v] = dp2[v] = 0;
        return;
    }
 
    for (auto u : graph[v]) {
        if (u.to == p)
            continue;
 
        dfs(u.to, v);
        dp1[v] = max(dp1[v], dp2[u.to] + u.w - dp[u.to]);
        dp2[v] += dp[u.to];
    }
    dp1[v] += dp2[v];
    dp[v] = max(dp1[v], dp2[v]);
}
 
int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    graph.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int from, to, w;
        scanf("%d%d%d", &from, &to, &w);
 
        graph[--from].push_back(edge(--to, w));
        graph[to].push_back(edge(from, w));
    }
 
    dp.resize(n);
    dp1.resize(n);
    dp2.resize(n);
    // all vertices could be root
    dfs(0);
 
    printf("%I64d", dp[0]);
 
    return 0;
}
