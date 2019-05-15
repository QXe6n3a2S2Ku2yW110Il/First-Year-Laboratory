#include <bits/stdc++.h>
 
using namespace std;
 
void rec(vector<int> &a, int n, int prev = 0) {
    for (int i : a)
        printf("%d ", i);
    printf("\n");
 
    for (int i = prev + 1; i <= n; ++i) {
        a.push_back(i);
        rec(a, n, i);
        a.pop_back();
    }
}
 
int main() {
    freopen("subsets.in", "r", stdin);
    freopen("subsets.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> a;
    rec(a, n);
 
    return 0;
}
