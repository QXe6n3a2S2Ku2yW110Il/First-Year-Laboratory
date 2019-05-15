#include <stdio.h>
#include <vector>
 
using namespace std;
 
unsigned int genRand = 0;
int genA, genB;
long long k;
 
unsigned int nextRand24() {
    genRand = genRand * genA + genB;
    return (genRand >> 8);
}
 
unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}
 
void MergeSort(vector<long long> &a, int left, int right, long long &ans) {
    if (right - left <= 1)
        return;
 
    int mid = (left + right) / 2;
    MergeSort(a, left, mid, ans);
    MergeSort(a, mid, right, ans);
 
    vector<long long> lbuf;
    lbuf.assign(a.begin() + left, a.begin() + mid);
 
    vector<long long> rbuf;
    rbuf.assign(a.begin() + mid, a.begin() + right);
 
    int lp = 0, rp = 0, lSize = (int) lbuf.size(), rSize = (int) rbuf.size();
    while (lp < lSize || rp < rSize) {
        if (lp < lSize && (rbuf[rp] - lbuf[lp] >= k || rp == rSize)) {
            ans += rSize - rp;
            ++lp;
        } else {
            ++rp;
        }
    }
 
    lp = 0;
    rp = 0;
    for (int i = left; i < right; ++i) {
        if (lp < lSize && (lbuf[lp] <= rbuf[rp] || rp == rSize))
            a[i] = lbuf[lp++];
        else
            a[i] = rbuf[rp++];
    }
}
 
int main() {
    int n;
    scanf("%d%I64d%d%d", &n, &k, &genA, &genB);
 
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + (int) nextRand32();
 
    long long ans = 0;
    MergeSort(a, 0, n + 1, ans);
 
    printf("%I64d", ans);
 
    return 0;
}
