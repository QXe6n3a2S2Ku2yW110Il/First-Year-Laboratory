#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

namespace global {
	int const INF = 1e9 + 7;
}
using namespace global;

namespace algo {
}
using namespace algo;

int main() {
	int n;
	scanf("%d", &n);

	std::vector<std::vector<int>> arr(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &arr[i][j]);
		}
	}

	std::vector<int> match(n + 1), row(n + 1), col(n + 1), from(n + 1);
	for (int i = 1; i <= n; ++i) {
		match[0] = i;
		int j0 = 0;

		std::vector<int> col_min(n + 1, INF);
		std::vector<bool> used(n + 1, false);
		do {
			used[j0] = true;
			int i0 = match[j0], delta = INF, j1 = 0;
			for (int j = 1; j <= n; ++j) {
				if (!used[j]) {
					int curr_val = arr[i0][j] - row[i0] - col[j];
					if (curr_val < col_min[j]) {
						col_min[j] = curr_val;
						from[j] = j0;
					}
					if (col_min[j] < delta) {
						delta = col_min[j];
						j1 = j;
					}
				}
			}

			for (int j = 0; j <= n; ++j) {
				if (used[j]) {
					row[match[j]] += delta;
					col[j] -= delta;
				} else {
					col_min[j] -= delta;
				}
			}

			j0 = j1;
		} while (match[j0] != 0);

		do {
			int j1 = from[j0];
			match[j0] = match[j1];
			j0 = j1;
		} while (j0 != 0);
	}

	int ans = 0;
	for (int j = 1; j <= n; ++j) {
		ans += arr[match[j]][j];
	}

	printf("%d\n", ans);
	for (int j = 1; j <= n; ++j) {
		printf("%d %d\n", match[j], j);
	}

	return 0;
}
