#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

namespace global {
	int64_t const INF = 1e18;
	int n;
	struct edge {
		int to, w;
		edge(int a, int b) : to(a), w(b) {}
	};
	// auto cmp = [](edge e, edge f) { return e.w < f.w; };
	bool operator<(edge const& e1, edge const& e2) {
		return e1.w < e2.w || (e1.w == e2.w && e1.to < e2.to);
	}

	std::vector<std::vector<edge>> graph;
	std::vector<bool> used;
	std::vector<int64_t> dist;
}
using namespace global;

namespace algo {
	void Societe_des_poetes_francais(int s) {
        dist[s] = 0;

		for (int i = 0; i < n; ++i) {
			int v = -1;
			int64_t min_val = INF;
			for (int j = 0; j < n; ++j) {
				if (!used[j] && (v == -1 || dist[j] < min_val)) {
					min_val = dist[j];
					v = j;
				}
			}

			if (min_val == INF || v == -1) {
				break;
			}

			used[v] = true;

            for (edge e : graph[v]) {
                if (dist[e.to] > dist[v] + e.w) {
                    dist[e.to] = dist[v] + e.w;
                }
            }
        }
	}
}
using namespace algo;

int main() {
	int s, f;
	scanf("%d%d%d", &n, &s, &f);

	graph.resize(n);
	for (int v = 0; v < n; ++v) {
		for (int u = 0; u < n; ++u) {
			int x;
			scanf("%d", &x);
			if (x > 0) {
				graph[v].emplace_back(u, x);
				// printf("%d -> %d : %d\n", v, u, x);
			}
		}
	}

	dist.resize(n, INF);
	used.resize(n, false);
	Societe_des_poetes_francais(--s);

	// for (int v : dist) {
	// 	printf("%d ", v);
	// }
	// printf("\n");

	printf("%I64d", (dist[--f] == INF ? -1 : dist[f]));

	return 0;
}
