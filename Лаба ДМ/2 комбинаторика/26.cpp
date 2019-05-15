#include <bits/stdc++.h>
 
using namespace std;
 
void readSet(int n, vector<vector<int>> &a) {
    int x;
    char c;
    vector<int> p;
    while (n > 0 && scanf("%d%c", &x, &c) == 2) {
        p.push_back(x);
        if (c == '\n') {
            a.push_back(p);
            p.clear();
            --n;
        }
    }
}
 
void writeSet(int n, vector<vector<int>> &a, vector<int> &t) {
    printf("%d %d\n", n, (int)a.size() + (int)t.size());
    for (auto &i : a) {
        for (int j : i)
            printf("%d ", j);
        printf("\n");
    }
    for (int i : t)
        printf("%d\n", i);
    printf("\n");
}
 
void solve(int n, int m) {
    vector<vector<int>> arr;
    readSet(m, arr);
 
    vector<int> used;
    bool notReplaced = true;
    for (int i = m - 1; i > -1 && notReplaced; --i) {
        if (!used.empty() && used.back() > arr[i].back()) {
            int pos = (int)used.size() - 1;
            while (pos > 0 && used[pos - 1] > arr[i].back())
                --pos;
 
            arr[i].push_back(used[pos]);
            //used.erase(find(used.begin(), used.end(), used[pos]));
            used.erase(used.begin() + pos);
            notReplaced = false;
        } else {
            for (int j = (int)arr[i].size() - 1; j > 0; --j) {
                if (!used.empty() && used.back() > arr[i][j]) {
                    int pos = (int)used.size() - 1;
                    while (pos > 0 && used[pos - 1] > arr[i].back())
                        --pos;
 
                    int save = arr[i][j];
                    arr[i][j] = used[pos];
                    //used.erase(find(used.begin(), used.end(), used[pos]));
                    used.erase(used.begin() + pos);
                    used.push_back(save);
                    sort(used.begin(), used.end());
                    notReplaced = false;
                    break;
                }
 
                used.push_back(arr[i][j]);
                //arr[i].erase(find(arr[i].begin(), arr[i].end(), arr[i][j]));
                arr[i].erase(arr[i].begin() + j);
                sort(used.begin(), used.end());
            }
 
            if (notReplaced) {
                used.push_back(arr[i][0]);
                arr.erase(arr.begin() + i);
                sort(used.begin(), used.end());
            }
        }
    }
 
    writeSet(n, arr, used);
}
 
int main() {
    freopen("nextsetpartition.in", "r", stdin);
    freopen("nextsetpartition.out", "w", stdout);
 
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        if (n == m && m == 0)
            return 0;
         
        solve(n, m);
    }
 
    return 0;
}
