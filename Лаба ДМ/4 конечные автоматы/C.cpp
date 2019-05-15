#include <stdio.h>
#include <stdlib.h> /*for exit*/
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int WHITE = 0, GRAY = 1, BLACK = 2, MOD = 1e9 + 7;
 
vector<bool> terminal, reachable;
vector<vector<int>> graph, inv_graph;
vector<int> topsorted, path_qty, color;
 
void find_vertices(int v) {
    if (color[v])
        return;
 
    color[v] = BLACK;
    reachable[v] = true;
    for (int u : inv_graph[v])
        find_vertices(u);
}
 
bool check_cycle(int v) {
    if (color[v] != GRAY)
        return true;
    if (!reachable[v])
        return false;
     
    color[v] = BLACK;
    bool result = true;
    for (int u : graph[v])
        result = result && check_cycle(u);
     
    return result;
}
 
void find_cycle(int v) {
    if (color[v] == GRAY) {
        if (check_cycle(v)) {
            printf("-1");
            exit(0);
        }
        return;
    }
    if (color[v] == BLACK)
        return;
     
    color[v] = GRAY;
    for (int u : graph[v])
        find_cycle(u);
    color[v] = BLACK;
    topsorted.push_back(v);
}
 
void call_dfs(void (*proc)(int v)) {
    color.assign(graph.size(), WHITE);
    proc(0);
}
 
int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
 
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
 
    terminal.resize(n, false);
    while (k--) {
        int v;
        scanf("%d", &v);
        terminal[--v] = true;
    }
 
    graph.resize(n);
    inv_graph.resize(n);
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
 
        graph[--from].push_back(--to);
        inv_graph[to].push_back(from);
    }
 
    color.resize(n, WHITE);
    reachable.resize(n, false);
    for (int i = 0; i < n; ++i) {
        if (terminal[i])
            find_vertices(i);
    }
 
    call_dfs(find_cycle);
    reverse(topsorted.begin(), topsorted.end());
     
    path_qty.resize(n, 0);
    path_qty[0] = 1;
    for (int v : topsorted) {
        for (int u : inv_graph[v])
            path_qty[v] = (path_qty[v] + path_qty[u]) % MOD;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (terminal[i])
            ans = (ans + path_qty[i]) % MOD;
    }
 
    printf("%d", ans);
 
    return 0;
}
