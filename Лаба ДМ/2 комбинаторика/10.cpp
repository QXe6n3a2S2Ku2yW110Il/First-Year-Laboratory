#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> a;
 
void rec(int k) {
    if (k == 0) {
        for (int i = 0; i < (int)a.size() - 1; ++i)
            printf("%d+", a[i]);
        printf("%d\n", a.back());
 
        return;
    }
 
    for (int i = 1; i <= k; ++i) {
        if (a.empty() || a.back() >= i) {
            a.push_back(i);
            rec(k - i);
            a.pop_back();
        }
    }
}
 
int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    rec(n);
 
    return 0;
}
