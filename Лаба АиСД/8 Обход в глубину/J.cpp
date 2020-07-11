#include <stdio.h>
#include <vector>
#include <cstdlib>

namespace global {
	std::vector<int> color;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v, int c = 0) {
		color[v] = c;

		for (int u : graph[v]) {
			if (color[u] == c) {
				printf("NO");
				exit(0);
			} else if (color[u] == -1) {
				dfs(u, c ^ 1);
			}
		}
	}
}
using namespace algo;

int main() {
	freopen("bipartite.in", "r", stdin);
	freopen("bipartite.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
		graph[to].push_back(from);
	}

	color.resize(n, -1);
	for (int v = 0; v < n; ++v) {
		if (color[v] == -1) {
			dfs(v);
		}
	}

	printf("YES");

	return 0;
}
