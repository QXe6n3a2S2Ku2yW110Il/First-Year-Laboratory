#include <bits/stdc++.h>
 
using namespace std;
 
void nextPerm(vector<int> &a) {
    int pos = (int)a.size() - 1;
    while (pos > 0 && a[pos] <= a[pos - 1])
        --pos;
    --pos;
 
    if (pos < 0) {
        a.assign((int)a.size(), 0);
        return;
    }
 
    int need = pos + 1;
    for (int i = pos + 1; i < (int)a.size(); ++i) {
        if (a[i] < a[need] && a[i] > a[pos])
            need = i;
    }
    swap(a[pos], a[need]);
    sort(a.begin() + pos + 1, a.end());
}
 
int main() {
    freopen("nextmultiperm.in", "r", stdin);
    freopen("nextmultiperm.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> p(n);
    for (int &i : p)
        scanf("%d", &i);
     
    nextPerm(p);
 
    for (int i : p)
        printf("%d ", i);
 
    return 0;
}
