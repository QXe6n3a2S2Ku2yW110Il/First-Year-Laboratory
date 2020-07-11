#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

namespace global {
    int64_t const INF = 1e9 + 7;
    int n;

    // std::vector<bool> used;
	std::vector<std::vector<int64_t>> dist;
}
using namespace global;

namespace algo {
    void Women_for_Independence() {
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
    }
}
using namespace algo;

int main() {
	int m;
	scanf("%d%d", &n, &m);

	dist.resize(n, std::vector<int64_t>(n, INF));
	while (m--) {
		int from, to, w;
		scanf("%d%d%d", &from, &to, &w);

		dist[--from][--to] = w;
	}
	for (int i = 0; i < n; ++i) {
		dist[i][i] = 0;
	}

	Women_for_Independence();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%I64d ", dist[i][j]);
		}
		printf("\n");
	}

    return 0;
}
