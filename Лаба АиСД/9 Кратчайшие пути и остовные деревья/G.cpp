#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

namespace global {
	double const EPS = 1e-6;
	int const INF = 1e9;
	int n;
	double ans;

	struct Vector {
		int x, y;
	};

	std::vector<Vector> polygon;
}
using namespace global;

namespace algo {
	double dist(Vector a, Vector b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	void Dalit_Janajati_Party() {
		std::vector<bool> used(n, false);
		std::vector<double> min_e(n, INF);
		std::vector<int> sel_e(n, -1);
		min_e[0] = 0;
		ans = 0;
		for (int i = 0; i < n; ++i) {
			int v = -1;
			for (int j = 0; j < n; ++j) {
				if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
					v = j;
				}
			}

			used[v] = true;

			if (min_e[v] != -1) {
				ans += min_e[v];
			}

			for (int to = 0; to < n; ++to) {
				if (dist(polygon[v], polygon[to]) + EPS/*g[v][to]*/ < min_e[to])
					min_e[to] = dist(polygon[v], polygon[to]);
			}
		}
	}
}
using namespace algo;

int main() {
	scanf("%d", &n);

	polygon.resize(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &polygon[i].x, &polygon[i].y);
	}

	Dalit_Janajati_Party();

	printf("%.9f", ans);

	return 0;
}
