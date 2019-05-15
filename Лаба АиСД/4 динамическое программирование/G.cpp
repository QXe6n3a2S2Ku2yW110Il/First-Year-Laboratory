#include <stdio.h>
#include <vector>
 
using namespace std;
 
int oneBitsQty(int x) {
    int res = 0;
    for (int i = 0; i < 32; ++i)
        res += ((x >> i) & 1);
 
    return res;
}
 
int diffBit(int x, int y) {
    for (int i = 0; i < 32; ++i) {
        if (((x >> i) & 1) != ((y >> i) & 1))
            return i;
    }
 
    return -1;
}
 
void writeBits(int x) {
    for (int i = 31; i > -1; --i)
        printf("%d", ((x >> i) & 1));
}
 
int main() {
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
 
    int n, m;
    scanf("%d%d", &n, &m);
 
    vector<int> left(n), right(n), change(n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d%d", &left[i], &right[i], &change[i]);
 
    int pow2n = (1 << n);
    vector<int> feel(pow2n, -1), from(pow2n, -1);
    feel[0] = m;
    from[0] = 0;
    for (int mask = 0; mask < pow2n; ++mask) {
        for (int v = 0; v < n; ++v) {
            if (((mask >> v) & 1) == 0)
                continue;
 
            int u = (mask ^ (1 << v));
            if (from[u] > -1 && left[v] <= feel[u] && feel[u] <= right[v]) {
                from[mask] = u;
                feel[mask] = feel[u] + change[v];
 
                /*printf("mask = ");
                writeBits(mask);
                printf("\nu = ");
                writeBits(u);
                printf("\nv = %d\n", v);*/
            }
        }
    }
 
    /*printf("feel:\n");
    for (int mask = 0; mask < pow2n; ++mask) {
        writeBits(mask);
        printf(" %d\n", feel[mask]);
    }
 
    printf("from:\n");
    for (int mask = 0; mask < pow2n; ++mask) {
        writeBits(mask);
        printf(" ");
        writeBits(from[mask]);
        printf("\n");
    }*/
 
    int currMask = 0;
    for (int mask = 0; mask < pow2n; ++mask) {
        if (from[mask] > -1 && oneBitsQty(currMask) < oneBitsQty(mask))
            currMask = mask;
    }
 
    vector<int> ans;
    while (currMask > 0) {
        ans.push_back(diffBit(currMask, from[currMask]));
        currMask = from[currMask];
    }
 
    printf("%d\n", (int)ans.size());
    for (int i = (int)ans.size() - 1; i > -1; --i)
        printf("%d ", ans[i] + 1);
 
    return 0;
}
