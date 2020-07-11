#include <stdio.h>
#include <vector>
#include <algorithm>

namespace global {
	int n, curr_comp, timer;
	std::vector<bool> used;
	std::vector<int> order, comp;
	std::vector<std::vector<int>> graph;
}
using namespace global;

namespace algo {
	void topsort(int v, int volume) {
		if (used[v]) {
			return;
		}
		used[v] = true;

		for (int u = 0; u < n; ++u) {
			if (graph[v][u] <= volume) {
				topsort(u, volume);
			}
		}

		order.push_back(v);
	}

	void find_component(int v, int volume) {
		if (comp[v] > 0) {
			return;
		}
		// printf("%d ", v);
		comp[v] = curr_comp;

		for (int u = 0; u < n; ++u) {
			if (graph[u][v] <= volume) {
				find_component(u, volume);
			}
		}
	}

	bool check(int volume) {
		// printf("===================\n");
		// printf("volume = %d\n", volume);
		timer = 0;
		order.clear();
		used.assign(n, false);
		for (int v = 0; v < n; ++v) {
			topsort(v, volume);
		}
		// printf("order: ");
		// for (int v : order) {
			// printf("%d ", v);
		// }
		// printf("\n");

		curr_comp = 0;
		comp.assign(n, 0);
		// printf("visited ");
		for (int v = n - 1; v > -1; --v) {
			if (comp[order[v]] == 0) {
				if (++curr_comp > 1) {
					// printf("\nvisited not all\n");
					return false;
				}
				// printf("starting at %d: ", order[v]);
				find_component(order[v], volume);
			}
		}

		// printf("\nall vertices are visited\n");
		return true;
	}
}
using namespace algo;

int main() {
	freopen("avia.in", "r", stdin);
	freopen("avia.out", "w", stdout);

	scanf("%d", &n);

	graph.resize(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &graph[i][j]);
		}
	}

	int left = -1, right = 1e9 + 1;
	while (right - left > 1) {
		int middle = left + (right - left) / 2;
		if (!check(middle)) {
			left = middle;
		} else {
			right = middle;
		}
	}

	printf("%d", right);

	return 0;
}
