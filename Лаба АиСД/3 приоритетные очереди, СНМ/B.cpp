#include <iostream>
#include <vector>

using namespace std;

struct dsu {
    int anc, min_v, max_v, sub_size;

    dsu() = default;
    dsu(int x): anc(x), min_v(x), max_v(x), sub_size(1) {}
};

vector<dsu> p;
dsu get(int x) {
    if (x == p[x].anc)
        return p[x];
    return p[x] = get(p[x].anc);
}
void unite(int a, int b) {
    a = get(a).anc;
    b = get(b).anc;
    if (a == b)
        return;

    if (rand() & 1) {
        p[b].anc = a;
        p[a].sub_size += p[b].sub_size;
        p[a].max_v = max(p[a].max_v, p[b].max_v);
        p[a].min_v = min(p[a].min_v, p[b].min_v);
    } else {
        p[a].anc = b;
        p[b].sub_size += p[a].sub_size;
        p[b].max_v = max(p[a].max_v, p[b].max_v);
        p[b].min_v = min(p[a].min_v, p[b].min_v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    p.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        p[i] = i;

    string s;
    while (cin >> s) {
        if (s == "union") {
            int x, y;
            cin >> x >> y;
            unite(x, y);
        }
        if (s == "get") {
            int x;
            cin >> x;

            auto res = get(x);
            printf("%d %d %d\n", res.min_v, res.max_v, res.sub_size);
        }
    }

    return 0;
}
