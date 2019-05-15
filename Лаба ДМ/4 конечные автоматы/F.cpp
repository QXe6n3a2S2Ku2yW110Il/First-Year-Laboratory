#include <stdio.h>
#include <vector>
 
using namespace std;
 
vector<bool> was, terminalA, terminalB;
vector<vector<int>> graphA, graphB;
 
bool dfs(int u, int v) {
    if (was[u])
        return true;
 
    was[u] = true;
    if (terminalA[u] ^ terminalB[v])
        return false;
     
    for (char c = 'a'; c <= 'z'; ++c) {
        int cm = c - 'a';
        if ((graphA[u][cm] == 0 && graphB[v][cm] != 0) ||
            (graphA[u][cm] != 0 && graphB[v][cm] == 0))
            return false;
         
        if (!dfs(graphA[u][cm], graphB[v][cm]))
            return false;
    }
 
    return true;
}
 
void parseInput(vector<bool> &terminal, vector<vector<int>> &graph) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
     
    terminal.resize(n, false);
    while (k--) {
        int v;
        scanf("%d", &v);
        terminal[--v] = true;
    }
 
    graph.resize(n, vector<int>('z' - 'a' + 1));
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
 
        graph[--from][letter - 'a'] = --to;
    }
}
 
int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);
 
    parseInput(terminalA, graphA);
    parseInput(terminalB, graphB);
 
    was.resize(graphA.size());
    printf((dfs(0, 0) ? "YES" : "NO"));
     
    return 0;
}
