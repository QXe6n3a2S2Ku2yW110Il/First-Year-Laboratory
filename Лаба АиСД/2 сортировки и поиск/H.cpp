#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int INF = 1e9 + 7;
 
unsigned int cur = 0;
unsigned int nextRand24(int a, int b) {
    cur = cur * a + b;
    return (cur >> 8);
}
 
void MergeSort(vector<int> &a, int left, int right, long long &inv_qty) {
    if (right - left <= 1)
        return;
 
    int mid = (left + right) / 2;
    MergeSort(a, left, mid, inv_qty);
    MergeSort(a, mid, right, inv_qty);
 
    vector<int> lbuf;
    lbuf.assign(a.begin() + left, a.begin() + mid);
    lbuf.push_back(INF);
 
    vector<int> rbuf;
    rbuf.assign(a.begin() + mid, a.begin() + right);
    rbuf.push_back(INF);
 
    int lp = 0, rp = 0;
    for (int i = left; i < right; ++i) {
        if (lbuf[lp] <= rbuf[rp]) {
            a[i] = lbuf[lp++];
        } else {
            a[i] = rbuf[rp++];
            inv_qty += (int)lbuf.size() - lp - 1;
        }
    }
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    int a, b;
    scanf("%d%d", &a, &b);
 
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = nextRand24(a, b) % m;
 
    long long ans = 0;
    MergeSort(arr, 0, n, ans);
 
    printf("%I64d", ans);
 
    return 0;
}
