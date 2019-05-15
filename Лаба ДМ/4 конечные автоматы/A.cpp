#include <stdio.h>
#include <string>
#include <vector>

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
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);

    string s;
    readString(s);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    int terminals[k];
    for (int i = 0; i < k; ++i)
        scanf("%d", &terminals[i]);

    vector<vector<int>> graph(n, vector<int>(26, -1));
    while (m--) {
        int from, to;
        char letter;
        scanf("%d%d %c", &from, &to, &letter);

        graph[--from][letter - 'a'] = --to;
    }

    int currVertex = 0;
    for (char c : s) {
        if (graph[currVertex][c - 'a'] > -1) {
            currVertex = graph[currVertex][c - 'a'];
        } else {
            printf("Rejects");
            return 0;
        }
    }

    ++currVertex;
    for (int v : terminals) {
        if (currVertex == v) {
            printf("Accepts");
            return 0;
        }
    }

    printf("Rejects");

    return 0;
}
