#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
bool readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1) {
        if (!(c == ' ' || c == '\n'))
            break;
    }
    s = c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
 
    return !s.empty();
}
 
const int MAX_N = 500000;
 
struct query {
    int to = 0, num = 0;
    query() = default;
    query(int a, int b) : to(a), num(b) {}
};
 
vector<vector<int>> graph(MAX_N);
vector<int> lcaClass(MAX_N), lca(MAX_N), rnk(MAX_N), ans(MAX_N);
vector<vector<query>> queries(MAX_N);
vector<bool> was(MAX_N, false);
 
int get(int v) {
    if (lcaClass[v] == v)
        return v;
    return lcaClass[v] = get(lcaClass[v]);
}
 
void unite(int v, int u) {
    int a = get(v), b = get(u);
    if (rnk[a] == rnk[b])
        ++rnk[a];
 
    // int newRoot = a, formerRoot = b;
    // if (rnk[newRoot] < rnk[formerRoot])
    //    swap(newRoot, formerRoot);
    // lcaClass[formerRoot] = newRoot;
    // lca[newRoot] = v;
    if (rnk[a] < rnk[b])
        swap(a, b);
    lcaClass[b] = a;
    lca[a] = v;
}
 
void dfs(int v) {
    was[v] = true;
    lcaClass[v] = v;
    for (int u : graph[v]) {
        if (!was[u]) {
            dfs(u);
            unite(v, u);
        }
    }
 
    for (auto &q : queries[v]) {
        if (was[v])
            ans[q.num] = lca[get(q.to)] + 1;
    }
}
 
int main() {
    int lines;
    scanf("%d", &lines);
 
    int queryQty = 0;
    while (lines--) {
        string s;
        readString(s);
        int x, y;
        scanf("%d%d", &x, &y);
 
        switch (s[0]) {
            case 'A':
                graph[--x].push_back(--y);
                graph[y].push_back(x);
                break;
            case 'G':
                queries[--x].push_back(query(--y, queryQty));
                queries[y].push_back(query(x, queryQty++));
                break;
        }
    }
 
    for (int i = 0; i < MAX_N; ++i)
        lca[i] = i;
 
    dfs(0);
 
    for (int i = 0; i < queryQty; ++i)
        printf("%d\n", ans[i]);
 
    return 0;
}
