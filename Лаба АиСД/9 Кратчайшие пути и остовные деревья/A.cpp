#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

namespace global {
	int const INF = 1e9 + 7;
	std::vector<int> dist;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void BrainFuckScheduler() {
		std::queue<int> q;
		q.push(0);
		dist[0] = 0;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int u : graph[v]) {
				if (dist[u] == INF) {
					q.push(u);
					dist[u] = dist[v] + 1;
				}
			}
		}
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
		graph[to].push_back(from);
	}

	dist.resize(n, INF);
	BrainFuckScheduler();

	for (int v : dist) {
		printf("%d ", v);
	}

	return 0;
}
