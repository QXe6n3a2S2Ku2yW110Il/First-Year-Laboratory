#include <stdio.h>
#include <vector>
#include <queue>
#include <string>
 
using namespace std;
 
int n, expect, maxDist;
vector<vector<int>> graph;
vector<int> prevVertex;
vector<bool> was;
 
void bfs(int v) {
    vector<int> dist(n);
    queue<int> q;
    q.push(v);
    dist[v] = 0;
    while (!q.empty()) {
        int curr = q.front();
        was[curr] = true;
        for (int u : graph[curr]) {
            if (!was[u]) {
                q.push(u);
                dist[u] = dist[curr] + 1;
                prevVertex[u] = curr;
            }
        }
 
        q.pop();
    }
 
    expect = 0, maxDist = 0;
    for (int i = 0; i < n; ++i) {
        if (maxDist < dist[i]) {
            expect = i;
            maxDist = dist[i];
        }
    }
}
 
int main() {
    scanf("%d", &n);
    if (n % 2 == 0) {
        printf("NO");
        return 0;
    }
 
    graph.resize(n);
    was.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        scanf("%d%d", &from, &to);
        graph[--from].push_back(--to);
        graph[to].push_back(from);
    }
 
    prevVertex.resize(n);
    bfs(0);
    fill(was.begin(), was.end(), false);
    bfs(expect);
    for (int i = 0; i < maxDist / 2; ++i)
        expect = prevVertex[expect];
 
    if (maxDist % 2 == 1 || graph[expect].size() != 2) {
        printf("NO");
        return 0;
    }
 
    printf("YES");
 
    return 0;
}
