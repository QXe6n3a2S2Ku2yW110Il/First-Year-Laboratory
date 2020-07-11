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

	void create_edge(int from, int to, int cap, int num) {
		edge *e1 = new edge(to, cap, num);
		edge *e2 = new edge(from, 0, -1);
		e1->inv = e2;
		e2->inv = e1;
		graph[from].push_back(e1);
		graph[to].push_back(e2);
	}

	typedef std::pair<int, std::vector<int>> decompose_t;
	decompose_t decomposotion(int s, int t) {
		std::vector<edge *> edges;
		std::vector<bool> used(n);

		int v = s;
		while (!used[v]) {
			if (v == t) {
				break;
			}

			used[v] = true;
			for (edge *e : graph[v]) {
				if (e->num > -1 && e->flow > 0 && !used[e->to]) {
					edges.push_back(e);
					v = e->to;
					break;
				}
			}
		}

		std::vector<int> edge_nums;
		int min_flow = INF;
		for (size_t i = 0; i < edges.size(); ++i) {
			min_flow = std::min(min_flow, edges[i]->flow);
			edge_nums.push_back(edges[i]->num);
		}
		for (size_t i = 0; i < edges.size(); ++i) {
			edges[i]->flow -= min_flow;
		}

		return std::make_pair(min_flow, edge_nums);
	}

	std::vector<decompose_t> full_decomposotion(int s, int t) {
		std::vector<decompose_t> res;
		// printf("in full\n");
		decompose_t dec = decomposotion(s, t);
		// printf("decomposed\n");
		while (!dec.second.empty()) {
			res.push_back(dec);
			dec = decomposotion(s, t);
			// printf("decomposed\n");
		}

		return res;
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
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &from, &to, &cap);

		create_edge(--from, --to, cap, i);
	}

	dinitz(0, n - 1);

	auto res = full_decomposotion(0, n - 1);

	printf("%d", static_cast<int>(res.size()));
	for (size_t i = 0; i < res.size(); ++i) {
		printf("\n%d %d", res[i].first, static_cast<int>(res[i].second.size()));
		for (int j : res[i].second) {
			printf(" %d", j + 1);
		}
	}

	for (auto &i : graph) {
		for (auto &j : i) {
			delete j;
		}
	}

	return 0;
}
