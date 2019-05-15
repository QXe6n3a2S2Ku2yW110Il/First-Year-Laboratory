#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int>> ans;
void rec(vector<int> &a, int n) {
    if ((int)a.size() == n) {
        ans.push_back(a);
        //for (int i : a)
        //    printf("%d", i);
        //printf("\n");
        return;
    }
 
    a.push_back(0);
    rec(a, n);
    a.pop_back();
    if (a.empty() || a.back() == 0) {
        a.push_back(1);
        rec(a, n);
        a.pop_back();
    }
}
 
int main() {
    freopen("vectors.in", "r", stdin);
    freopen("vectors.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> a;
    rec(a, n);
 
    printf("%d\n", (int)ans.size());
    for (auto &i : ans) {
        for (int j : i)
            printf("%d", j);
        printf("\n");
    }
 
    return 0;
}
