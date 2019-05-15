#include <bits/stdc++.h>
 
using namespace std;
 
int n;
vector<vector<int>> graph, transposed_graph;
vector<bool> was;
vector<int> topsorted, color;
 
void topsort(int v) {
    if (was[v])
        return;
    was[v] = true;
 
    for (int u : graph[v])
        topsort(u);
 
    topsorted.push_back(v);
}
 
void component(int v, int cnt) {
    if (was[v])
        return;
    was[v] = true;
    color[v] = cnt;
 
    for (int u : transposed_graph[v])
        component(u, cnt);
}
 
int get_pos(int x) {
    if (x > 0)
        return x - 1;
    return n - x - 1;
}
 
int main() {
    int m;
    scanf("%d%d", &n, &m);
 
    graph.resize(2 * n);
    transposed_graph.resize(2 * n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
 
        graph[get_pos(-a)].push_back(get_pos(b));
        transposed_graph[get_pos(b)].push_back(get_pos(-a));
        graph[get_pos(-b)].push_back(get_pos(a));
        transposed_graph[get_pos(a)].push_back(get_pos(-b));
    }
 
    was.resize(2 * n, false);
    for (int i = 0; i < 2 * n; ++i)
        topsort(i);
 
    fill(was.begin(), was.end(), false);
    color.resize(2 * n);
    int cnt = 0;
    for (int i = 2 * n - 1; i > -1; --i) {
        if (!was[topsorted[i]])
            component(topsorted[i], ++cnt);
    }
 
    for (int i = 1; i <= n; ++i) {
        if (color[get_pos(i)] == color[get_pos(-i)]) {
            printf("YES");
            return 0;
        }
    }
 
    printf("NO");
 
    return 0;
}
