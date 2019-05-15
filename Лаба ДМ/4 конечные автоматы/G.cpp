#include <stdio.h>
#include <vector>
#include <queue>
 
using namespace std;
 
vector<bool> terminalA, terminalB;
vector<vector<int>> graphA, graphB;
 
void parseInput(vector<bool> &terminal, vector<vector<int>> &graph) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    ++n;
     
    terminal.resize(n, false);
    while (k--) {
        int v;
        scanf("%d", &v);
        terminal[v] = true;
    }
 
    graph.resize(n, vector<int>('z' - 'a' + 1));
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
 
        graph[from][letter - 'a'] = to;
    }
}
 
bool check() {
    queue<pair<int, int>> q;
    vector<vector<bool>> was(graphA.size(), vector<bool>(graphB.size()));
    q.push({1, 1});
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
 
        int u = curr.first, v = curr.second;
        if (terminalA[u] ^ terminalB[v])
            return false;
 
        was[u][v] = true;
        for (char c = 'a'; c <= 'z'; ++c) {
            int cm = c - 'a';
            if (!was[graphA[u][cm]][graphB[v][cm]])
                q.push({graphA[u][cm], graphB[v][cm]});
        }
    }
 
    return true;
}
 
int main() {
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);
 
    parseInput(terminalA, graphA);
    parseInput(terminalB, graphB);
 
    printf((check() ? "YES" : "NO"));
     
    return 0;
}
