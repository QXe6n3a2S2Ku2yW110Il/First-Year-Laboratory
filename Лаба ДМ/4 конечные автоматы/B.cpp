#include <stdio.h>
#include <string>
#include <vector>
#include <set>
 
using namespace std;
 
bool readString(string &s) {
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == ' ' || c == '\n')
            break;
        s += c;
    }
 
    return !s.empty();
}
 
int main() {
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
 
    string s;
    readString(s);
 
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
 
    bool terminal[n];
    for (int i = 0; i < k; ++i) {
        int vertex;
        scanf("%d", &vertex);
        terminal[--vertex] = true;
    }
     
    vector<vector<vector<int>>> graph(n, vector<vector<int>>(26));
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);
        graph[--from][letter - 'a'].push_back(--to);
    }
 
    set<int> prev, curr;
    prev.insert(0);
    for (char c : s) {
        int edge = c - 'a';
        for (int v : prev) {
            for (int u : graph[v][edge])
                curr.insert(u);
        }
 
        prev = curr;
        curr.clear();
    }
 
    for (int v : prev) {
        if (terminal[v]) {
            printf("Accepts");
            return 0;
        }
    }
 
    printf("Rejects");
 
    return 0;
}
