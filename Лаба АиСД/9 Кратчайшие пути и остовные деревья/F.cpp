#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

namespace global {
    int const INF = 1e9;
    int n;

	struct edge {
		int from, to, w;
		edge(int a, int b, int c) : from(a), to(b), w(c) {}
	};

    // std::vector<bool> used;
	std::vector<int> dist, pr, vertices;
	std::vector<edge> edges;
}
using namespace global;

namespace algo {
	void find_neg_cycle(int v) {
		// for (int vv : pr) {
		// 	printf("%d ", vv);
		// }
		// printf("\n");
		// printf("in\n");
		for (int i = 0; i < n; ++i) {
			v = pr[v];
		}
		// printf("found\n");

		for (int u = pr[v]; u != v; u = pr[u]) {
			vertices.push_back(u);
		}
		vertices.push_back(v);
		vertices.push_back(pr[v]);

		std::reverse(vertices.begin(), vertices.end());
	}

	void Bellman_Ford_Moore(int s) {
        dist.assign(n + 1, INF);
		pr.assign(n + 1, 0);
        dist[s] = 0;

        for (int k = 0; k < n; ++k) {
            for (edge e : edges) {
				if (dist[e.from] < INF && dist[e.to] > dist[e.from] + e.w) {
	                dist[e.to] = std::max(-INF, dist[e.from] + e.w);
					pr[e.to] = e.from;
				}
            }
        }
		for (edge e : edges) {
			if (dist[e.from] < INF && dist[e.to] > dist[e.from] + e.w) {
				pr[e.to] = e.from;
				find_neg_cycle(e.to);
				return;
			}
		}
    }
}
using namespace algo;

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			scanf("%d", &x);

			if (x != INF) {
				edges.emplace_back(i, j, x);
			}
		}
		edges.emplace_back(n, i, 0);
	}

	Bellman_Ford_Moore(n);

	if (vertices.empty()) {
		printf("NO");
	} else {
		printf("YES\n%d\n", static_cast<int>(vertices.size()));
		for (int v : vertices) {
			printf("%d ", v + 1);
		}
	}

    return 0;
}
