#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

namespace global {
	std::vector<bool> used;
	std::vector<int> tin, fup;
	std::set<int> cutpoints;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v, int p = -1) {
		static int timer = 0;
		used[v] = true;
		tin[v] = fup[v] = timer++;
		int child = 0;
		for (int u : graph[v]) {
			if (u == p) {
				continue;
			}
			if (used[u]) {
				fup[v] = std::min(fup[v], tin[u]);
			} else {
				dfs(u, v);
				fup[v] = std::min(fup[v], fup[u]);
				if (fup[u] >= tin[v] && p != -1) {
					cutpoints.insert(v);
				}
				++child;
			}
		}

		if (p == -1 && child > 1) {
			cutpoints.insert(v);
		}
	}
}
using namespace algo;

int main() {
	freopen("points.in", "r", stdin);
	freopen("points.out", "w", stdout);

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

	printf("%d\n", static_cast<int>(cutpoints.size()));
	for (int num : cutpoints) {
		printf("%d ", num + 1);
	}

	return 0;
}
