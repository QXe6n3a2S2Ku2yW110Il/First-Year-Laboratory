#include <stdio.h>
#include <vector>
#include <cstdlib>

namespace global {
	enum class color {
		WHITE, GRAY, BLACK
	};
	std::vector<color> col;
	std::vector<int> prev;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void find_cycle(int v) {
		static std::vector<int> cycle;

		if (!cycle.empty() && v == cycle[0]) {
			printf("YES\n");
			for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
				printf("%d ", *it + 1);
			}

			return;
		}

		cycle.push_back(v);
		find_cycle(prev[v]);
	}

	void dfs(int v) {
		if (col[v] == color::BLACK) {
			return;
		}
		if (col[v] == color::GRAY) {
			find_cycle(v);
			exit(0);
		}
		col[v] = color::GRAY;

		for (int u : graph[v]) {
			prev[u] = v;
			dfs(u);
		}

		col[v] = color::BLACK;
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

	col.resize(n, color::WHITE);
	prev.resize(n);
	for (int v = 0; v < n; ++v) {
		dfs(v);
	}

	printf("NO");

	return 0;
}
