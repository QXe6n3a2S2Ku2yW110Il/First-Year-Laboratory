#include <stdio.h>
#include <vector>

namespace global {
	enum class color {
		WHITE, GRAY, BLACK
	};

	std::vector<color> col;
	std::vector<int> vertices;
	std::vector<std::vector<int>> graph;
}
using namespace global;

bool dfs(int v) {
	if (col[v] == color::BLACK) {
		return true;
	}
	if (col[v] == color::GRAY) {
		return false;
	}
	col[v] = color::GRAY;

	bool res = true;
	for (int u : graph[v]) {
		res = (res && dfs(u));
	}

	vertices.push_back(v);
	col[v] = color::BLACK;
	return res;
}

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
	for (int v = 0; v < n; ++v) {
		if (!dfs(v)) {
			printf("-1");
			return 0;
		}
	}

	for (auto it = vertices.rbegin(); it != vertices.rend(); ++it) {
		printf("%d ", *it + 1);
	}

	return 0;
}
