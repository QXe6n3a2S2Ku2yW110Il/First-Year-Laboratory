#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

namespace global {
	std::vector<bool> used;
	std::vector<int> tin, fup;
	std::set<int> bridges;
	struct edge {
		int to, num;
	};
	std::vector<std::vector<edge>> graph;
}
using namespace global;

namespace algo {
	void dfs(int v, int p = 0) {
		static int timer = 0;
		used[v] = true;
		tin[v] = fup[v] = timer++;
		for (auto& u : graph[v]) {
			if (u.to == p) {
				continue;
			}
			if (used[u.to]) {
				fup[v] = std::min(fup[v], tin[u.to]);
			} else {
				dfs(u.to, v);
				fup[v] = std::min(fup[v], fup[u.to]);
				if (fup[u.to] > tin[v]) {
					bridges.insert(u.num);
				}
			}
		}
	}
}
using namespace algo;

int main() {
	freopen("bridges.in", "r", stdin);
	freopen("bridges.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back({--to, i});
		graph[to].push_back({from, i});
	}

	used.resize(n);
	tin.resize(n);
	fup.resize(n);
	for (int v = 0; v < n; ++v) {
		if (!used[v]) {
			dfs(v);
		}
	}

	printf("%d\n", static_cast<int>(bridges.size()));
	for (int num : bridges) {
		printf("%d ", num + 1);
	}

	return 0;
}
