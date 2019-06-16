#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
const int N = 1u << 24u;
unsigned int arr[N + 1];
 
unsigned int a, b, cur = 0u;
unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8u;
}
 
int main() {
    // diff[0] = arr[0], diff[i] = arr[i] - arr[i - 1]
    // pref[0] = 0, pref[i] = (k = 0..i-1) (partial + arr[k])
 
    int m, q;
    scanf("%d%d%u%u", &m, &q, &a, &b);
 
    // arr as diff
    while (m--) {
        auto sum = nextRand();
        auto l = nextRand();
        auto r = nextRand();
        if (l > r)
            swap(l, r);
 
        arr[l] += sum;
        arr[r + 1] -= sum;
    }
 
    // change arr from diff to pref
    for (int ch = 0; ch < 2; ++ch) {
        for (int i = 1; i < N; ++i)
            arr[i] += arr[i - 1];
    }
 
    unsigned int ans = 0;
    while (q--) {
        auto l = nextRand();
        auto r = nextRand();
        if (l > r)
            swap(l, r);
 
        ans += arr[r] - (l == 0 ? 0u : arr[l - 1]);
    }
 
    printf("%u", ans);
 
    return 0;
}
