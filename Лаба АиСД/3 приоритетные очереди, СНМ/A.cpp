#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &p[i]);
    for (int i = 0; i < n; ++i) {
        if ((2 * i + 1 < n && p[i] > p[2 * i + 1]) ||
            (2 * i + 2 < n && p[i] > p[2 * i + 2])) {
            printf("NO");
            return 0;
        }
    }

    printf("YES");

    return 0;
}
