#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
 
using namespace std;
 
const int MOD = 1e9 + 7, MAX_N = 100;
 
vector<bool> terminal, nTerminal(MAX_N);
vector<vector<int>> sum, nGraph(MAX_N);
vector<vector<pair<int, int>>> graph;
 
int rec(int v, int len) {
    if (sum[v][len] != -1)
        return sum[v][len];
     
    if (len == 0)
        return sum[v][len] = nTerminal[v];
     
    sum[v][len] = 0;
    for (int u : nGraph[v])
        sum[v][len] = (sum[v][len] + rec(u, len - 1)) % MOD;
    return sum[v][len];
}
 
void NFAtoDFA() {
    set<set<int>> vs;
    map<set<int>, int> qty;
    queue<set<int>> q;
 
    q.push({0});
    vs.insert({0});
    int cnt = 0;
    qty[{0}] = cnt++;
    nTerminal[0] = terminal[0];
    while (!q.empty()) {
        auto pd = q.front();
        q.pop();
        for (int c = 'a'; c <= 'z'; ++c) {
            set<int> curr;
            for (int p : pd) {
                for (auto v : graph[p]) {
                    if (v.second == c)
                        curr.insert(v.first);
                }
            }
 
            if (curr.empty())
                continue;
             
            if (vs.count(curr) == 0) {
                vs.insert(curr);
                qty[curr] = cnt++;
                q.push(curr);
 
                for (int p : curr) {
                    if (terminal[p]) {
                        nTerminal[qty[curr]] = true;
                        break;
                    }
                }
            }
 
            nGraph[qty[pd]].push_back(qty[curr]);
        }
    }
}
 
int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
     
    int n, m, k, l;
    scanf("%d%d%d%d", &n, &m, &k, &l);
 
    terminal.resize(n, false);
    while (k--) {
        int v;
        scanf("%d", &v);
        terminal[--v] = true;
    }
 
    graph.resize(n);
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
 
        graph[--from].push_back({--to, letter});
    }
 
    NFAtoDFA();
 
    sum.resize(MAX_N, vector<int>(l + 1, -1));
    printf("%d", rec(0, l));
 
    return 0;
}
