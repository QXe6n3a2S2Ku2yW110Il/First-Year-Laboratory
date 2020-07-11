#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

namespace global {
    int64_t const INF = 4e18;
    int n;

	struct edge {
		int from, to;
		int64_t w;
		edge(int a, int b, int64_t c) : from(a), to(b), w(c) {}
	};

    // std::vector<bool> used;
	std::vector<int64_t> dist;
	std::vector<edge> edges;
	std::vector<std::vector<int>> graph;
	std::vector<bool> used;
}
using namespace global;

namespace algo {
	void Bellman_Ford_Moore(int s) {
		dist.assign(n, INF);
		dist[s] = 0;

		for (int k = 0; k < n - 1; ++k) {
			for (edge e : edges) {
				if (dist[e.from] != INF) {
					// printf("%lld -> ", dist[e.to]);
					dist[e.to] = std::min(dist[e.to], std::max(-INF, dist[e.from] + e.w));
					// printf("%lld", dist[e.to]);
					// printf(" (%lld + %lld)\n", dist[e.from], e.w);
				}
			}
		}
	}

	void find_neg_cycle(int v) {
		if (used[v]) {
			return;
		}

		used[v] = true;
		for (int u : graph[v]) {
			find_neg_cycle(u);
		}
	}
}
using namespace algo;

int main() {
	int m, s;
	scanf("%d%d%d", &n, &m, &s);

	graph.resize(n);
	while (m--) {
		int from, to;
		int64_t w;
		scanf("%d%d%I64d", &from, &to, &w);

		graph[--from].push_back(--to);
		edges.emplace_back(from, to, w);
	}

	Bellman_Ford_Moore(--s);

	used.resize(n);
	for (edge e : edges) {
		if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.w) {
			find_neg_cycle(e.from);
		}
	}

	for (int v = 0; v < n; ++v) {
		if (used[v]) {
			printf("-\n");
		} else if (dist[v] == INF) {
			printf("*\n");
		} else {
			printf("%I64d\n", dist[v]);
		}
	}

    return 0;
}
