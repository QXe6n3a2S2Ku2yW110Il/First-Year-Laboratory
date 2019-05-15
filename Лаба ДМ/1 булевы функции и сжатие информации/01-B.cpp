#include <stdio.h>
#include <vector>
#include <set>
 
using namespace std;
 
int update_func(vector<set<int>> &a) {
    vector<set<int>> res;
    for (auto &i : a) {
        if ((i.size() == 1 && *i.begin() == 0) || i.empty())
            continue;
        res.push_back(i);
    }
 
    swap(res, a);
 
    return (int)a.size();
}
 
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
 
    vector<set<int>> horn_func(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            scanf("%d", &x);
 
            if (x == 1)
                horn_func[i].insert(j + 1);
            if (x == 0)
                horn_func[i].insert(-(j + 1));
        }
    }
    set<int> one;
    one.insert(0);
 
    vector<int> lonely_args;
    do {
        lonely_args.clear();
        for (int i = 0; i < k; ++i) {
            if (horn_func[i].size() == 1)
                lonely_args.push_back(*horn_func[i].begin());
        }
 
        for (int arg : lonely_args) {
            for (int i = 0; i < k; ++i) {
                if (horn_func[i].count(arg))
                    horn_func[i] = one;
                if (horn_func[i].count(-arg)) {
                    if (horn_func[i].size() == 1) {
                        printf("YES");
                        return 0;
                    }
                    horn_func[i].erase(-arg);
                }
            }
 
            k = update_func(horn_func);
        }
    } while (!lonely_args.empty());
 
    printf("NO");
 
    return 0;
}
