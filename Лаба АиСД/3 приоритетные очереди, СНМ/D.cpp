#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p;

int get(int x) {
    if (p[x] == x)
        return x;
    return p[x] = get(p[x]);
}

void unite(int a, int b) {
    p[get(a)] = get(b);
}

int main() {
    int n;
    scanf("%d", &n);

    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);

        x = get(x - 1);
        printf("%d ", x + 1);
        unite(x, (x + 1) % n);
    }

    return 0;
}
