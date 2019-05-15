#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p;
int find_set(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_set(p[x]);
}

void unite(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (rand() & 1)
        p[y] = x;
    else
        p[x] = y;
}

struct infile {
    bool cut;
    int a;
    int b;
};

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        scanf("%d%d", &from, &to);

        graph[--from].push_back(--to);
        graph[to].push_back(from);
    }

    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;

    vector<infile> in(k);
    for (int i = 0; i < k; ++i) {
        char c;
        scanf(" %c", &c);

        if (c == 'a') {
            while (c != ' ')
                scanf("%c", &c);

            int a, b;
            scanf("%d%d", &a, &b);

            in[i] = { false, a, b };
        } else {
            while (c != ' ')
                scanf("%c", &c);

            int a, b;
            scanf("%d%d", &a, &b);

            in[i] = { true, a, b };
        }
    }

    vector<bool> ans;
    for (int i = k - 1; i > -1; --i) {
        if (in[i].cut) {
            unite(in[i].a - 1, in[i].b - 1);
        } else {
            if (find_set(in[i].a - 1) == find_set(in[i].b - 1))
                ans.push_back(true);
            else
                ans.push_back(false);
        }
    }

    for (int i = (int)ans.size() - 1; i > -1; --i) {
        if (ans[i])
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
