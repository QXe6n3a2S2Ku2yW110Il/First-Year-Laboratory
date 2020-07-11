#include <stdio.h>
#include <vector>

namespace global {
	std::vector<bool> used;
	std::vector<int> vertices, comp;
	std::vector<std::vector<int>> graph, rgraph;
}
using namespace global;

namespace algo {
	void topsort(int v) {
		if (used[v]) {
			return;
		}
		used[v] = true;

		for (int u : graph[v]) {
			topsort(u);
		}

		vertices.push_back(v);
	}

	int num = 0;
	void find_comp(int v) {
		if (used[v]) {
			return;
		}
		used[v] = true;
		comp[v] = num;

		for (int u : rgraph[v]) {
			find_comp(u);
		}
	}
}
using namespace algo;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	rgraph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
		rgraph[to].push_back(from);
	}

	used.resize(n);
	for (int v = 0; v < n; ++v) {
		topsort(v);
	}

	used.assign(n, false);
	comp.resize(n);
	for (int v = n - 1; v > -1; --v) {
		if (!used[vertices[v]]) {
			++num;
			find_comp(vertices[v]);
		}
	}

	printf("%d\n", num);
	for (int v : comp) {
		printf("%d ", v);
	}

	return 0;
}
