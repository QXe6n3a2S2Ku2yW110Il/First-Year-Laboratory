#include <stdio.h>
#include <vector>

using namespace std;

vector<int> p, r, c;

int get(int x, int &res) {
    res ^= c[x];

    if (p[x] == x)
        return x;

    res ^= 1;
    return get(p[x], res);
}

void unite(int a, int b) {
    int resA = 0, resB = 0;
    a = get(a, resA);
    b = get(b, resB);

    if (a == b)
        return;

    if (r[a] < r[b])
        swap(a, b);
    p[b] = a;
    if (r[a] == r[b])
        ++r[a];
    if (resA == resB)
        c[b] ^= 1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
    r.resize(n, 0);
    c.resize(n, 1);

    int shift = 0;
    while (m--) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);
        a = (a + shift) % n;
        b = (b + shift) % n;

        if (x == 0) {
            unite(a, b);
        } else {
            int resA = 0, resB = 0;
            a = get(a, resA);
            b = get(b, resB);

            if (a != b) {
                printf("YES\n");
                continue;
            }
            if (resA == resB) {
                printf("YES\n");
                shift = (shift + 1) % n;
            } else {
                printf("NO\n");
            }
        }
    }

    return 0;
}
