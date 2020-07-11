#include <stdio.h>
#include <vector>

namespace global {
	int max_color = 0;
	using std::vector;
	vector<bool> used;
	vector<int> tin, fup, color;
	struct edge {
		edge(int a, int b) : to(a), num(b) {}
		int to, num;
	};
	vector<vector<edge>> graph;

	int const MAX_M = 200000;
	int refactor[MAX_M + 1];
}
using namespace global;

namespace algo {
	void dfs(int v, int p = -1) {
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
			}
		}
	}

	void paint(int v, int c, int p = -1) {
		used[v] = true;
		// printf("in v = %d\n", v);
		for (auto& u : graph[v]) {
			if (u.to == p) {
				continue;
			}
			// printf("considering %d -> %d\n", v, u.to);
			if (!used[u.to]) {
				if (fup[u.to] >= tin[v]) {
					color[u.num] = ++max_color;
					// printf("1: color[%d] = %d\n", u.num, max_color);
					paint(u.to, max_color, v);
				} else {
					color[u.num] = c;
					// printf("2: color[%d] =  %d\n", u.num, c);
					paint(u.to, c, v);
				}
			} else if (tin[u.to] < tin[v]) {
				color[u.num] = c;
				// printf("3: color[%d] = %d\n", u.num, c);
			}
			// printf("4\n");
		}
	}
}
using namespace algo;

int main() {
	freopen("biconv.in", "r", stdin);
	freopen("biconv.out", "w", stdout);

	int n, m;
	scanf("%d%d", &n, &m);

	graph.resize(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);

		graph[--from].emplace_back(--to, i);
		graph[to].emplace_back(from, i);
	}

	used.resize(n);
	tin.resize(n);
	fup.resize(n);
	for (int v = 0; v < n; ++v) {
		if (!used[v]) {
			dfs(v);
		}
	}

	used.assign(n, false);
	color.resize(m);
	for (int v = 0; v < n; ++v) {
		if (!used[v]) {
			paint(v, ++max_color);
		}
	}

	int curr_num = 0;
	for (int i : color) {
		if (refactor[i] == 0) {
			refactor[i] = ++curr_num;
		}
	}

	printf("%d\n", curr_num);
	for (int i : color) {
		printf("%d ", refactor[i]);
	}

	return 0;
}
