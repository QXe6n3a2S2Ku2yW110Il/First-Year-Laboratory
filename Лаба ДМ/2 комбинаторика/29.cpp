#include <bits/stdc++.h>
 
using namespace std;
 
void readPartition(vector<int> &p) {
    int x;
    while (scanf("+%d", &x) == 1)
        p.push_back(x);
}
 
void nextPartition(vector<int> &p) {
    int n = (int)p.size();
    --p.back();
    ++p[n - 2];
     
    if (p[n - 2] > p.back()) {
        p[n - 2] += p.back();
        p.pop_back();
    } else {
        while (p[n - 2] * 2 <= p.back()) {
            p.push_back(p.back() - p[n - 2]);
            ++n;
            p[n - 2] = p[n - 3];
        }
    }
}
 
void writePartition(int n, vector<int> &p) {
    printf("%d=%d", n, p[0]);
    for (int i = 1; i < (int)p.size(); ++i)
        printf("+%d", p[i]);
}
 
int main() {
    freopen("nextpartition.in", "r", stdin);
    freopen("nextpartition.out", "w", stdout);
 
    int n;
    vector<int> p(1);
    scanf("%d=%d", &n, &p[0]);
    readPartition(p);
 
    if ((int)p.size() == 1 && p[0] == n) {
        printf("No solution");
        return 0;
    }
 
    nextPartition(p);
 
    writePartition(n, p);
 
    return 0;
}
