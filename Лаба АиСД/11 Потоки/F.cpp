#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

namespace global {
	struct edge {
		int to, cap, flow, num;
		edge *inv;

		edge(int to, int cap, int num): to(to), cap(cap), flow(0), num(num), inv(nullptr) {}
	};

	int n;
	const int INF = 1e9 + 7;
	std::vector<std::vector<edge*>> graph;
	std::vector<int> dist, head, min_cap;
}
using namespace global;

namespace algo {
	bool bfs(int s, int t, int x) {
		dist.assign(n + 2, -1);
		dist[s] = 0;

		std::queue<int> q;
		q.push(s);

		while (!q.empty()) {
			int v = q.front();
			q.pop();

			for (edge *e : graph[v]) {
				if (dist[e->to] == -1 && e->cap - e->flow >= x) {
					dist[e->to] = dist[v] + 1;
					q.push(e->to);
				}
			}
		}

		return dist[t] != -1;
	}

	int dfs(int v, int t, int c_min, int x) {
		if (v == t) {
			return c_min;
		}

		while (head[v] < static_cast<int>(graph[v].size())) {
			edge *e = graph[v][head[v]];
			if (dist[v] + 1 == dist[e->to] && e->cap - e->flow >= x) {
				int pushed = dfs(e->to, t, std::min(c_min, e->cap - e->flow), x);
				if (pushed > 0) {
					e->flow += pushed;
					e->inv->flow -= pushed;
					return pushed;
				}
			}

			++head[v];
		}

		return 0;
	}

	long long dinitz(int s, int t) {
		int x = 1 << 30;
		long long flow = 0;
		while (x > 0) {
			while (bfs(s, t, x)) {
				head.assign(n + 2, 0);
				long long push;
				while ((push = dfs(s, t, INF, x))) {
					flow += push;
				}
			}

			x /= 2;
		}

		return flow;
	}

	void create_edge(int from, int to, int cap, int num) {
		edge *e1 = new edge(to, cap, num);
		edge *e2 = new edge(from, 0, -1);
		e1->inv = e2;
		e2->inv = e1;
		graph[from].push_back(e1);
		graph[to].push_back(e2);
		min_cap[num] = cap;
	}

	void quit() {
		for (auto &i : graph) {
			for (auto &j : i) {
				delete j;
			}
		}

		exit(0);
	}
}
using namespace algo;

int main() {
	int m;
	scanf("%d%d", &n, &m);

	dist.resize(n + 2);
	head.resize(n + 2);
	graph.resize(n + 2);
	min_cap.resize(m);
	for (int i = 0; i < m; ++i) {
		int from, to, min_cap, cap;
		scanf("%d%d%d%d", &from, &to, &min_cap, &cap);

		create_edge(0, to, min_cap, i);
		create_edge(from, to, cap - min_cap, i);
		create_edge(from, n + 1, min_cap, i);
	}

	dinitz(0, n + 1);

	for (edge *e : graph[0]) {
		if (e->flow != e->cap) {
			printf("NO");
			quit();
			return 0;
		}
	}

	std::vector<int> res(m);
	for (int v = 1; v < n + 1; ++v) {
		for (edge *e : graph[v]) {
			if (e->num != -1 && e->to != n + 1) {
				res[e->num] = e->flow + min_cap[e->num];
			}
		}
	}

	printf("YES\n");
	for (int i : res) {
		printf("%d\n", i);
	}
	quit();

	return 0;
}
