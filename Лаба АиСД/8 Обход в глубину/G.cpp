#include <stdio.h>
#include <vector>

namespace global {
	int curr_num = 0;
	std::vector<int> comp;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v) {
		comp[v] = curr_num;
		for (int u : graph[v]) {
			if (comp[u] == 0) {
				dfs(u);
			}
		}
	}
}
using namespace algo;

int main() {
	freopen("components.in", "r", stdin);
	freopen("components.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
		graph[to].push_back(from);
	}

	comp.resize(n);
	for (int v = 0; v < n; ++v) {
		if (comp[v] == 0) {
			++curr_num;
			dfs(v);
		}
	}

	printf("%d\n", curr_num);
	for (int v : comp) {
		printf("%d ", v);
	}

	return 0;
}
