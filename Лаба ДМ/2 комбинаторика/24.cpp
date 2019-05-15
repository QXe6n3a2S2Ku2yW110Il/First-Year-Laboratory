#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> nextPerm(vector<int> a) {
    for (int i = (int)a.size() - 2; i > -1; --i) {
        if (a[i] < a[i + 1]) {
            int min_pos = i + 1;
            for (int j = i + 1; j < (int)a.size(); ++j) {
                if (a[j] < a[min_pos] && a[j] > a[i])
                    min_pos = j;
            }
 
            swap(a[i], a[min_pos]);
            reverse(a.begin() + i + 1, a.end());
            return a;
        }
    }
 
    vector<int> kek((int)a.size(), 0);
    return kek;
}
 
vector<int> prevPerm(vector<int> a) {
    for (int i = (int)a.size() - 2; i > -1; --i) {
        if (a[i] > a[i + 1]) {
            int max_pos = i + 1;
            for (int j = i + 1; j < (int)a.size(); ++j) {
                if (a[j] > a[max_pos] && a[j] < a[i])
                    max_pos = j;
            }
 
            swap(a[i], a[max_pos]);
            reverse(a.begin() + i + 1, a.end());
            return a;
        }
    }
 
    vector<int> kek((int)a.size(), 0);
    return kek;
}
 
int main() {
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> p(n);
    for (int &i : p)
        scanf("%d", &i);
     
    vector<int> prevP = prevPerm(p);
    for (int i : prevP)
        printf("%d ", i);
    printf("\n");
     
    vector<int> nextP = nextPerm(p);
    for (int i : nextP)
        printf("%d ", i);
 
    return 0;
}
