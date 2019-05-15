#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = (int)1e9  + 7;

vector<int> mainP, segmP, maxSet;

void init(int n, vector<int> &p) {
    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
}

int get(int x, vector<int> &p) {
    if (p[x] == x)
        return x;
    return p[x] = get(p[x], p);
}

void unite(int a, int b, vector<int> &p) {
    a = get(a, p);
    b = get(b, p);

    if (rand() & 1)
        swap(a, b);

    p[b] = a;
}

void uniteSeg(int a, int b) {
    while (maxSet[get(a, segmP)] + 1 <= b) {
        int tmp = maxSet[get(a, segmP)] + 1;
        // printf("unite %d %d\n", a + 1, tmp + 1);
        maxSet[get(a, segmP)] = max(maxSet[get(a, segmP)], maxSet[get(tmp, segmP)]);
        unite(a, tmp, mainP);
        unite(a, tmp, segmP);
        a = tmp;
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    init(n, mainP);
    init(n, segmP);
    init(n, maxSet);

    while (q--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        --y;
        --z;

        if (x == 1)
            unite(y, z, mainP);
        if (x == 2)
            uniteSeg(y, z);
        if (x == 3) {
            if (get(y, mainP) == get(z, mainP))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    return 0;
}
