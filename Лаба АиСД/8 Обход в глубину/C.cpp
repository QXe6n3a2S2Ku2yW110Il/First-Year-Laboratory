#include <stdio.h>
#include <vector>

namespace global {
	int const INF = 1e9 + 7;
	struct integer {
		int val;
		integer(int x) : val(x) {}
		integer operator+(integer const& i) {
			if (val == INF || i.val == INF) {
				return INF;
			}
			return i.val + val;
		}
		bool operator<(integer const& i) const {
			return val < i.val;
		}
		operator int() {
			return val;
		}
	};
	struct vert {
		int to;
		integer w;
	};
	std::vector<bool> used;
	std::vector<int> vertices;
	std::vector<std::vector<vert>> graph;
}
using namespace global;

namespace algo {
	void topsort(int v) {
		if (used[v]) {
			return;
		}
		used[v] = true;

		for (auto &u : graph[v]) {
			topsort(u.to);
		}

		vertices.push_back(v);
	}
}
using namespace algo;

int main() {
	int n, m, s, f;
	scanf("%d%d%d%d", &n, &m, &s, &f);

	graph.resize(n);
	while (m--) {
		int from, to, w;
		scanf("%d%d%d", &from, &to, &w);

		graph[--from].push_back({--to, w});
	}

	used.resize(n);
	for (int v = 0; v < n; ++v) {
		topsort(v);
	}

	std::vector<integer> dist(n, INF);
	dist[--s] = 0;
	for (int v = n - 1; v > -1; --v) {
		for (auto &u : graph[vertices[v]]) {
			dist[u.to] = std::min(dist[u.to], dist[vertices[v]] + u.w);
		}
	}

	if (dist[--f] == INF) {
		printf("Unreachable");
	} else {
		printf("%d", static_cast<int>(dist[f]));
	}

	return 0;
}
