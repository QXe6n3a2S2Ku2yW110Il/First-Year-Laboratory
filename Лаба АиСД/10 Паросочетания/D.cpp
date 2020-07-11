#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

namespace global {
	std::vector<bool> used;
	std::vector<std::vector<int>> graph;
	std::vector<int> match;
	std::set<int> Rwas;
}
using namespace global;

namespace algo {
	bool Kuhn_Munkres_algorithm(int v) {
		if (used[v]) {
			return false;
		}
		used[v] = true;

		for (int u : graph[v]) {
			Rwas.insert(u);
			if (match[u] == -1 || Kuhn_Munkres_algorithm(match[u])) {
				match[u] = v;
				return true;
			}
		}

		return false;
	}

	void solve() {
		int n, m;
		scanf("%d%d", &n, &m);

		graph.clear();
		graph.resize(n);
		for (int v = 0; v < n; ++v) {
			std::vector<bool> is_used(m, false);
			int t;
			while (~scanf("%d", &t)) {
				if (t == 0) {
					break;
				}
				is_used[--t] = true;
			}

			for (int u = 0; u < m; ++u) {
				if (!is_used[u]) {
					graph[v].push_back(u);
				}
			}
		}

		match.assign(m, -1);
		used.assign(n, false);
		for (int v = 0; v < n; ++v) {
			if (Kuhn_Munkres_algorithm(v)) {
				used.assign(n, false);
			}
		}

		std::set<int> not_free;
		for (int u = 0; u < m; ++u) {
			if (match[u] != -1) {
				not_free.insert(match[u]);
			}
		}

		used.assign(n, false);
		Rwas.clear();
		for (int v = 0; v < n; ++v) {
			if (!not_free.count(v)) {
				Kuhn_Munkres_algorithm(v);
			}
		}

		std::vector<int> Lwas;
		for (int v = 0; v < n; ++v) {
			if (used[v]) {
				Lwas.push_back(v);
			}
		}

		printf("%d\n", static_cast<int>(Lwas.size() + m - Rwas.size()));
		printf("%d %d\n", static_cast<int>(Lwas.size()), static_cast<int>(m - Rwas.size()));
		for (int v : Lwas) {
			printf("%d ", v + 1);
		}
		printf("\n");
		for (int u = 0; u < m; ++u) {
			if (!Rwas.count(u)) {
				printf("%d ", u + 1);
			}
		}
		printf("\n\n");
	}
}
using namespace algo;

int main() {
	int test;
	scanf("%d", &test);

	while (test--) {
		solve();
	}

	return 0;
}
