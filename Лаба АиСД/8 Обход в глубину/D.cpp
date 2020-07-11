#include <stdio.h>
#include <vector>

namespace global {
	std::vector<bool> first_type, second_type, used;
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
			first_type[v] = first_type[v] || !second_type[u];
			second_type[v] = second_type[v] || !first_type[u];
		}
	}
}
using namespace algo;

int main() {
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);

	graph.resize(n);
	while (m--) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].push_back(--to);
	}

	used.resize(n);
	first_type.resize(n);
	second_type.resize(n);
	dfs(--s);

	printf((first_type[s] ? "First" : "Second"));
	printf(" player wins");

	return 0;
}
