#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <iostream>
#include <set>

namespace global {
	long long const INF = 1e18 + 1e10;
	int n, e_num = 0;

	struct edge {
		int from, to, cap;
		long long flow;
		int price;

		edge(int f, int t, int fl, int c, int p): from(f), to(t), cap(c), flow(fl), price(p) {}
	};

	std::vector<edge> edges;
	std::vector<std::vector<int>> graph;
	std::set<std::pair<long long, int>> q;
	std::vector<long long> pot, dist;
	std::vector<bool> used;
	std::vector<int> match;
}
using namespace global;

namespace algo {
	void Ford_Bellman() {
		dist.assign(n, INF);
		dist[0] = 0;
		bool updated;
		do {
			updated = false;
			for (int i = 0; i < e_num; ++i) {
				if (edges[i].cap - edges[i].flow == 0 || dist[edges[i].from] == INF) {
					continue;
				}
				if (dist[edges[i].to] > dist[edges[i].from] + edges[i].price) {
					dist[edges[i].to] = dist[edges[i].from] + edges[i].price;
					updated = true;
				}
			}
		} while (updated);
	}

	void Dijkstra() {
		q.clear();
		q.emplace(0, 0);
		dist.assign(n, INF);
		dist[0] = 0;

		while (!q.empty()) {
			int v = (*q.begin()).second;
			q.erase(q.begin());

			for (int i : graph[v]) {
				edge e = edges[i];
				if (e.cap - e.flow == 0) {
					continue;
				}

				long long w = edges[i].price + pot[v] - pot[e.to];
				// printf("w: %lld\n", w);
				if (dist[e.to] > dist[v] + w) {
					q.erase(std::make_pair(dist[e.to], e.to));
					dist[e.to] = dist[v] + w;
					q.emplace(dist[e.to], e.to);
					match[e.to] = i;
				}
			}
		}
	}

	long long calc(long long flow) {
		// printf("=====\n");
		// for (edge e : edges) {
		// 	printf("%d %d %lld %d %d\n", e.from + 1, e.to + 1, e.flow, e.cap, e.price);
		// }
		// printf("=====\n");
		long long res = 0;
		Ford_Bellman();
		// printf("pot: ");
		for (int i = 0; i < n; ++i) {
			pot[i] = dist[i];
			// printf("%lld ", pot[i]);
		}
		// printf("\n");

		do {
			Dijkstra();
			// printf("match: ");
			// for (int i : match) {
			// 	printf("%d ", i);
			// }
			// printf("\n");
			if (dist[n - 1] == INF) {
				return res;
			}

			// printf("pot: ");
			for (int i = 0; i < n; ++i) {
				pot[i] = std::min(pot[i] + dist[i], INF);
				// printf("%lld ", pot[i]);
			}
			// printf("\n");

			long long push = flow;
			int curr_v = n - 1;
			while (curr_v != 0) {
				edge e = edges[match[curr_v]];
				push = std::min(push, e.cap - e.flow);
				curr_v = e.from;
				// printf("push = %lld, curr_v = %d\n", push, curr_v + 1);
			}
			flow -= push;
			// printf("flow = %lld, push = %lld\n", flow, push);

			curr_v = n - 1;
			while (curr_v != 0) {
				edge e = edges[match[curr_v]];
				edges[match[curr_v]].flow += push;
				edges[match[curr_v] ^ 1].flow -= push;
				res += push * e.price;
				curr_v = e.from;
			}
			// printf("res = %lld\n", res);
		} while (flow != 0);

		return res;
	}

	void create_edge(int from, int to, int cap, int price) {
		edges.emplace_back(from, to, 0, cap, price);
		graph[from].push_back(e_num++);
		edges.emplace_back(to, from, cap, cap, -price);
		graph[to].push_back(e_num++);
	}
}
using namespace algo;

int main() {
	int m;
	scanf("%d%d", &n, &m);

	used.resize(n);
	dist.resize(n);
	match.resize(n);
	pot.resize(n);
	graph.resize(n);
	long long max_flow = 0;
	while (m--) {
		int from, to, cap, price;
		scanf("%d%d%d%d", &from, &to, &cap, &price);

		create_edge(--from, --to, cap, price);
		if (from == 0) {
			max_flow += cap;
		}
	}

	printf("%I64d", calc(max_flow));

	return 0;
}
