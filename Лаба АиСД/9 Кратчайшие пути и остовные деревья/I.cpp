#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

namespace global {
	int const INF = 1e9 + 7;
	int n, m, res;

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
	void kruskal(int x) {
		dsu::p.assign(n, 0);
		for (int i = 0; i < n; ++i) {
			dsu::p[i] = i;
		}

		int cnt = 0, min_w = INF, max_w = -INF;
		for (int i = x; i < m; ++i) {
			if (dsu::get(graph[i].from) != dsu::get(graph[i].to)) {
				min_w = std::min(min_w, graph[i].w);
				max_w = std::max(max_w, graph[i].w);
				++cnt;
				dsu::unite(graph[i].from, graph[i].to);
			}
		}

		if (cnt == n - 1) {
			res = std::min(res, max_w - min_w);
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

	std::sort(graph.begin(), graph.end());

	res = INF - (-INF) + 1;
	for (int i = 0; i < m; ++i) {
		kruskal(i);
	}

	res == 2 * INF + 1 ? printf("NO") : printf("YES\n%d", res);

	return 0;
}
