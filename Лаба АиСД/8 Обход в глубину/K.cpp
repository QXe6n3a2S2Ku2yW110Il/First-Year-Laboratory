#include <stdio.h>
#include <vector>
#include <cstdlib>

namespace global {
	int max_color = 0;
	std::vector<bool> used;
	std::vector<int> tin, fup, color;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v, int p = -1) {
		static int timer = 0;
		used[v] = true;
		tin[v] = fup[v] = timer++;
		for (int u : graph[v]) {
			if (u == p) {
				continue;
			}
			if (used[u]) {
				fup[v] = std::min(fup[v], tin[u]);
			} else {
				dfs(u, v);
				fup[v] = std::min(fup[v], fup[u]);
			}
		}
	}

	void paint(int v, int c) {
		color[v] = c;
		for (int u : graph[v]) {
			if (color[u] == 0) {
				if (fup[u] > tin[v]) {
					paint(u, ++max_color);
				} else {
					paint(u, c);
				}
			}
		}
	}
}
using namespace algo;

int main() {
	freopen("bicone.in", "r", stdin);
	freopen("bicone.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
		graph[to].push_back(from);
	}

	used.resize(n);
	tin.resize(n);
	fup.resize(n);
	for (int v = 0; v < n; ++v) {
		if (!used[v]) {
			dfs(v);
		}
	}

	color.resize(n);
	for (int v = 0; v < n; ++v) {
		if (color[v] == 0) {
			paint(v, ++max_color);
		}
	}

	printf("%d\n", max_color);
	for (int c : color) {
		printf("%d ", c);
	}

	return 0;
}
