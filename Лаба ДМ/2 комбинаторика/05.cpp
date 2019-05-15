#include <bits/stdc++.h>
 
using namespace std;
 
int n, k;
 
void writeln(vector<int> &s) {
    for (int c : s)
        printf("%d", c);
    printf("\n");
}
 
int changePos(vector<int> &d, vector<int> &s) {
    for (int i = 0; i < n; ++i) {
        if (d[i] == 0 && s[i] == -1)
            s[i] = 1;
        else if (d[i] == k - 1 && s[i] == 1)
            s[i] = -1;
        else
            return i;
    }
 
    // end of all vectors
    return 0;
}
 
void getNext(int p, vector<int> &d, vector<int> &s) {
    if (s[p] == 1)
        ++d[p];
    if (s[p] == -1)
        --d[p];
}
 
int main() {
    freopen("telemetry.in", "r", stdin);
    freopen("telemetry.out", "w", stdout);
 
    scanf("%d%d", &n, &k);
    vector<int> currDigit(n, 0);
    vector<int> sign(n, 1);
 
    int qty = 1;
    for (int i = 0; i < n; ++i)
        qty *= k;
    for (int i = 0; i < qty; ++i) {
        writeln(currDigit);
        int pos = changePos(currDigit, sign);
        getNext(pos, currDigit, sign);
    }
 
    return 0;
}
