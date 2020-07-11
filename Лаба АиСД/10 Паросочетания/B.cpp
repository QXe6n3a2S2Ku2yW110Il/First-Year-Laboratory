#include <stdio.h>
#include <vector>
#include <algorithm>

namespace global {
	std::vector<bool> used;
	std::vector<std::vector<int>> graph;
	std::vector<int> mt;
}
using namespace global;

namespace algo {
	bool Kuhn_Munkres_algorithm(int v) {
	    if (used[v]) {
			return false;
		}
		used[v] = true;
		for (auto u : graph[v]) {
			if (mt[u] == -1 || Kuhn_Munkres_algorithm(mt[u])) {
				mt[u] = v;
				return true;
			}
		}
		return false;
	}
}
using namespace algo;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
	}

	mt.resize(n, -1);
	for (int i = 0; i < n; ++i) {
		used.assign(n, false);
		Kuhn_Munkres_algorithm(i);
	}

	int res = 0;
	for (int match : mt) {
		res += match != -1;
	}

	printf("%d", n - res);

	return 0;
}
