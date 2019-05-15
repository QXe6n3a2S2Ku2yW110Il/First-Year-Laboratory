#include <stdio.h>
#include <vector>
 
using namespace std;
 
int lower_search(vector<int> &a, int x) {
    int left = -1, right = (int)a.size() - 1;
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }
 
    if (a[right] != x)
        return -1;
    return right;
}
 
int upper_search(vector<int> &a, int x) {
    int left = 0, right = (int)a.size();
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (a[middle] <= x)
            left = middle;
        else
            right = middle;
    }
 
    if (a[left] != x)
        return -1;
    return left;
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    int m;
    scanf("%d", &m);
    while (m--) {
        int x;
        scanf("%d", &x);
 
        int l_pos = lower_search(a, x), r_pos = upper_search(a, x);
        if (l_pos == -1 || r_pos == -1)
            printf("-1 -1\n");
        else
            printf("%d %d\n", l_pos + 1, r_pos + 1);
    }
 
    return 0;
}
