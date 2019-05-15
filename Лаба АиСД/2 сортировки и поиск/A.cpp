#include <stdio.h>
#include <vector>
 
using namespace std;
 
const int INF = 1e9 + 7;
 
void MergeSort(vector<int> &a, int left, int right) {
    if (right - left <= 1)
        return;
 
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid, right);
 
    vector<int> lbuf;
    lbuf.assign(a.begin() + left, a.begin() + mid);
    lbuf.push_back(INF);
 
    vector<int> rbuf;
    rbuf.assign(a.begin() + mid, a.begin() + right);
    rbuf.push_back(INF);
 
    int lp = 0, rp = 0;
    for (int i = left; i < right; ++i) {
        if (lbuf[lp] <= rbuf[rp])
            a[i] = lbuf[lp++];
        else
            a[i] = rbuf[rp++];
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    MergeSort(a, 0, n);
 
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
 
    return 0;
}
