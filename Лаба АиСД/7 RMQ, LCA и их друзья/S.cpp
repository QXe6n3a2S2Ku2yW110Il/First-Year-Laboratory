#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int LOG2_MAX_N = 17;
 
vector<vector<int>> graph, dp;
vector<int> tin, tout;
int timer = 0;
 
void dfs(int v, int p = 0) {
    tin[v] = timer++;
    dp[v][0] = p;
 
    for (int u : graph[v]) {
        if (u != p)
            dfs(u, v);
    }
 
    tout[v] = timer++;
}
 
inline bool isAncestor(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}
 
int lca(int v, int u) {
    for (int k = LOG2_MAX_N; k > -1; --k) {
        if (!isAncestor(dp[v][k], u))
            v = dp[v][k];
    }
    if (!isAncestor(v, u))
        v = dp[v][0];
 
    return v;
}
 
void solve(int n) {
    graph.assign(n, vector<int>());
    for (int i = 1; i < n; ++i) {
        int from, to;
        scanf("%d%d", &from, &to);
 
        graph[--from].push_back(--to);
        graph[to].push_back(from);
    }
    dp.assign(n, vector<int>(LOG2_MAX_N + 1));
    tin.assign(n, 0);
    tout.assign(n, 0);
    int root = 0;
    dfs(root);
 
    for (int k = 1; k <= LOG2_MAX_N; ++k) {
        for (int i = 0; i < n; ++i)
            dp[i][k] = dp[dp[i][k - 1]][k - 1];
    }
 
    int m;
    scanf("%d", &m);
    while (m--) {
        char type;
        int x, y;
        scanf("\n%c", &type);
        switch (type) {
            case '?':
                scanf("%d%d", &x, &y);
                --x;
                --y;
                printf("%d\n", (lca(x, y) ^ lca(x, root) ^ lca(y, root)) + 1);
                break;
            case '!':
                scanf("%d", &root);
                --root;
                break;
        }
    }
}
 
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n > 0)
            solve(n);
        else
            break;
    }
 
    return 0;
}
