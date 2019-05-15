#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
void kth_element(vector<int> &a, int k, int left, int right) {
    if (right - left <= 1)
        return;
 
    int x = a[rand() % (right - left) + left], lt = left, eq = left;
    for (int i = left; i < right; ++i) {
        if (a[i] == x)
            swap(a[i], a[eq++]);
        if (a[i] < x) {
            swap(a[i], a[eq]);
            swap(a[eq++], a[lt++]);
        }
    }
 
    if (k == x)
        return;
    if (k >= left && lt > k)
        kth_element(a, k, left, lt);
    else
        kth_element(a, k, eq, right);
}
 
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    --k;
 
    int A, B, C;
    vector<int> a(n);
    scanf("%d%d%d%d%d", &A, &B, &C, &a[0], &a[1]);
    for (int i = 2; i < n; ++i)
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
 
    kth_element(a, k, 0, n);
    printf("%d", a[k]);
 
    return 0;
}
