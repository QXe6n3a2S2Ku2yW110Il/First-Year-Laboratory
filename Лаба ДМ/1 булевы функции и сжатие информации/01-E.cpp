#include <stdio.h>
#include <vector>
 
using namespace std;
 
vector<vector<int>> from;
int max_depth = 0;
void dfs(int v, int depth) {
    if (from[v].empty()) {
        max_depth = max(max_depth, depth);
        return;
    }
 
    for (int u : from[v])
        dfs(u, depth + 1);
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    int qty_args = 0;
    vector<pair<vector<int>, vector<int>>> comps;
    from.resize(n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
         
        if (x > 0) {
            vector<int> nums(x);
            for (int j = 0; j < x; ++j) {
                scanf("%d", &nums[j]);
                from[i].push_back(--nums[j]);
            }
            vector<int> table(1 << x);
            for (int j = 0; j < (1 << x); ++j)
                scanf("%d", &table[j]);
             
            comps.push_back({nums, table});
        }
        if (x == 0)
            ++qty_args;
    }
 
    dfs(n - 1, 0);
    printf("%d\n", max_depth);
 
    for (int num = 0; num < (1 << qty_args); ++num) {
        vector<int> curr_val(n);
        int curr_arg = 0, curr_comp = 0;
        for (int i = 0; i < n; ++i) {
            if (from[i].empty())
                curr_val[i] = ((num >> (qty_args - (++curr_arg))) & 1);
            else {
                int curr_index = 0;
                for (int j : comps[curr_comp].first)
                    curr_index = (curr_index << 1) + curr_val[j];
                curr_val[i] = comps[curr_comp++].second[curr_index];
            }
        }
 
        printf("%d", curr_val.back());
    }
 
    return 0;
}
