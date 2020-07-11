#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

namespace global {
	struct edge {
		int to, cap, flow;
		edge *inv;

		edge(int to, int cap): to(to), cap(cap), flow(0), inv(nullptr) {}
	};

	int n;
	const int INF = 1e9 + 7;
	std::vector<std::vector<edge*>> graph;
	std::vector<int> dist, head;
}
using namespace global;

namespace algo {
	bool bfs(int s, int t, int x) {
		dist.assign(n, -1);
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
				head.assign(n, 0);
				long long push;
				while ((push = dfs(s, t, INF, x))) {
					flow += push;
				}
			}

			x /= 2;
		}

		return flow;
	}

	void create_edge(int from, int to, int cap) {
		edge *e1 = new edge(to, cap);
		edge *e2 = new edge(from, 0);
		e1->inv = e2;
		e2->inv = e1;
		graph[from].push_back(e1);
		graph[to].push_back(e2);
	}

	void after_dinitz_dfs(int v, std::vector<int> &res, std::vector<bool> &used) {
		if (used[v]) {
			return;
		}

		used[v] = true;
		res.push_back(v + 1);

		for (edge *e : graph[v]) {
			if (e->flow < e->cap) {
				after_dinitz_dfs(e->to, res, used);
			}
		}
	}
}
using namespace algo;

int main() {
	int m;
	scanf("%d%d", &n, &m);

	dist.resize(n);
	head.resize(n);
	graph.resize(n);
	int from, to, cap;
	while (m--) {
		scanf("%d%d%d", &from, &to, &cap);

		create_edge(--from, --to, cap);
		create_edge(to, from, cap);
	}

	// printf("End of read\n");
	// printf(/*"res = %lld"*/"%I64d", dinitz(0, n - 1));
	dinitz(0, n - 1);

	std::vector<bool> used(n);
	std::vector<int> res;
	after_dinitz_dfs(0, res, used);

	printf("%d\n", static_cast<int>(res.size()));
	for (int i : res) {
		printf("%d ", i);
	}

	for (auto &i : graph) {
		for (auto &j : i) {
			delete j;
		}
	}

	return 0;
}
