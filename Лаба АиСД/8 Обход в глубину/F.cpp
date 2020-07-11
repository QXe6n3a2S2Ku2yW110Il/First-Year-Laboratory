#include <stdio.h>
#include <vector>
#include <algorithm>

namespace global {
	std::vector<bool> used;
	std::vector<int> order;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v) {
		if (used[v]) {
			return;
		}
		used[v] = true;

		for (int u : graph[v]) {
			dfs(u);
		}

		order.push_back(v);
	}
}
using namespace algo;

int main() {
	freopen("hamiltonian.in", "r", stdin);
	freopen("hamiltonian.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
	}

	used.resize(n);
	for (int v = 0; v < n; ++v) {
		dfs(v);
	}

	for (int v = n - 1; v > 0; --v) {
		int from = order[v], to = order[v - 1];
		if (std::find(graph[from].begin(), graph[from].end(), to) == graph[from].end()) {
			printf("NO");
			return 0;
		}
	}

	printf("YES");

	return 0;
}
