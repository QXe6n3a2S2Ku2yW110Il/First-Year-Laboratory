#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
const int MAX_SYMB = 1000;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    int n, m, k;
    cin >> n >> m >> k;
 
    vector<string> arrs(n);
    for (int i = 0; i < n; ++i)
        cin >> arrs[i];
 
    for (int i = 0; i < k; ++i) {
        vector<vector<int>> cnt(MAX_SYMB);
        for (int j = 0; j < n; ++j)
            cnt[arrs[j][m - 1 - i]].push_back(j);
 
        vector<string> curr_res;
        for (int j = 0; j < MAX_SYMB; ++j) {
            for (auto q : cnt[j])
                curr_res.push_back(arrs[q]);
        }
 
        swap(curr_res, arrs);
    }
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << arrs[i][j];
        cout << '\n';
    }
 
    return 0;
}
