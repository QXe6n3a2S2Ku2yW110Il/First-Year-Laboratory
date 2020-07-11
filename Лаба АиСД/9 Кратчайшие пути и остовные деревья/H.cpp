#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

namespace global {
	int n, m, cost;

	namespace dsu {
		std::vector<int> p;

		int get(int v) {
			return (v == p[v]) ? v : (p[v] = get(p[v]));
		}

		void unite(int a, int b) {
			a = get(a);
			b = get(b);
			if (rand() & 1)
				std::swap(a, b);
			if (a != b)
				p[a] = b;
		}
	}

	struct edge {
		int from, to, w;

		edge(int a, int b, int c) : from(a), to(b), w(c) {}
		bool operator <(const edge &e) const {
			return w < e.w;
		}
	};

	std::vector<edge> graph;
}
using namespace global;

namespace algo {
	void kruskal() {
		std::sort(graph.begin(), graph.end());

		dsu::p.resize(n);
		for (int i = 0; i < n; ++i) {
			dsu::p[i] = i;
		}

		cost = 0;
		for (int i = 0; i < m; ++i) {
			if (dsu::get(graph[i].from) != dsu::get(graph[i].to)) {
				cost += graph[i].w;
				dsu::unite(graph[i].from, graph[i].to);
			}
		}
	}
}
using namespace algo;

int main() {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; ++i) {
		int from, to, w;
		scanf("%d%d%d", &from, &to, &w);

		graph.emplace_back(--from, --to, w);
	}

	kruskal();

	printf("%d", cost);

	return 0;
}
