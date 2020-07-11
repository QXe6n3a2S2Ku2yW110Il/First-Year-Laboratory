#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

namespace global {
	int m;
	std::vector<bool> used;
	std::vector<std::vector<int>> graph;
	std::vector<int> mt;
	std::set<int> Lnotwas, Rwas;
}
using namespace global;

namespace algo {
	void find_vertex_cover(int v) {
		if (used[v]) {
			return;
		}
		used[v] = true;

		if (v < m) {
			Lnotwas.erase(v);
		} else {
			Rwas.insert(v);
		}

		for (int u : graph[v]) {
			find_vertex_cover(u);
		}
	}
}
using namespace algo;

int main() {
	int n;
	scanf("%d%d", &m, &n);

	graph.resize(m + n);
	for (int v = 0; v < m; ++v) {
		int k;
		scanf("%d", &k);

		for (int j = 0; j < k; ++j) {
			int x;
			scanf("%d", &x);
			graph[v].push_back(m + --x);
		}
	}

	std::set<int> free;
	for (int v = 0; v < m; ++v) {
		int x;
		scanf("%d", &x);

		if (x == 0) {
			free.insert(v);
		} else {
			graph[m + --x].push_back(v);
		}

		Lnotwas.insert(v);
	}

	used.resize(m + n);
	for (int v : free) {
		find_vertex_cover(v);
	}

	printf("%d\n", static_cast<int>(Lnotwas.size() + Rwas.size()));
	printf("%d", static_cast<int>(Lnotwas.size()));
	for (int v : Lnotwas) {
		printf(" %d", v + 1);
	}
	printf("\n%d", static_cast<int>(Rwas.size()));
	for (int v : Rwas) {
		printf(" %d", v - m + 1);
	}

	return 0;
}
