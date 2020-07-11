#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

namespace global {
    int64_t const INF = 1e9 + 7;
    int n;
    struct edge {
        int to;
		int64_t w;
        edge(int a, int64_t b) : to(a), w(b) {}
    };
    // auto cmp = [](edge e, edge f) { return e.w < f.w; };
    bool operator<(edge const& e1, edge const& e2) {
        return e1.w < e2.w || (e1.w == e2.w && e1.to < e2.to);
    }

    std::vector<std::vector<edge>> graph;
    // std::vector<bool> used;
    std::vector<int64_t> dist;
}
using namespace global;

namespace algo {
    void Societe_des_poetes_francais(int s) {
        std::set<edge> q;
        // for (int i = 0; i < n; ++i) {
        //  q.emplace(i, INF);
        // }
        q.emplace(s, 0);
        dist[s] = 0;

        while (!q.empty()) {
            int v = q.begin()->to;
            q.erase(q.begin());

            for (edge e : graph[v]) {
                if (dist[e.to] > dist[v] + e.w) {
                    q.erase({e.to, dist[e.to]});
                    dist[e.to] = dist[v] + e.w;
                    q.emplace(e.to, dist[e.to]);
                }
            }
        }
    }
}
using namespace algo;

int main() {
	int m;
	scanf("%d%d", &n, &m);

    graph.resize(n);
	while (m--) {
		int from, to, w;
		scanf("%d%d%d", &from, &to, &w);

		graph[--from].emplace_back(--to, w);
		graph[to].emplace_back(from, w);
	}

    dist.resize(n, INF);
    // used.resize(n, false);
    Societe_des_poetes_francais(0);

    for (int64_t v : dist) {
		printf("%I64d ", v);
    }
    printf("\n");

    return 0;
}
