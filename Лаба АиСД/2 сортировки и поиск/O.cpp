#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int n;
vector<pair<int, int>> a;
bool NotFoundAns = false;
 
bool sorted(vector<int> &x) {
    int pos = 0, range = (int)x.size();
    while (pos < range && x[pos] == 0)
        ++pos;
    while (pos < range && x[pos] == 1)
        ++pos;
 
    return pos == range;
}
 
void rec(int n, vector<int> &v, int left, int right) {
    if (n == 2) {
        if (!(v[0] == 1 && v[1] == 0))
            NotFoundAns = true;
        return;
    }
 
    vector<int> curr;
    curr.assign(v.begin() + 1, v.end());
    if (!sorted(curr)) {
        rec(n - 1, curr, left + 1, right);
        if (v[0] == 0) {
            for (int i = right; i > left; --i)
                a.push_back({left, i});
        } else {
            for (int i = left; i < right; ++i)
                a.push_back({i, i + 1});
        }
 
        return;
    }
 
    curr.clear();
    curr.assign(v.begin(), v.end() - 1);
    if (!sorted(curr)) {
        rec(n - 1, curr, left, right - 1);
        if (v.back() == 0) {
            for (int i = right; i > left; --i)
                a.push_back({i - 1, i});
        } else {
            for (int i = left; i < right; ++i)
                a.push_back({i, right});
        }
 
        return;
    }
 
    NotFoundAns = true;
    return;
}
 
int main() {
    while (scanf("%d", &n) == 1) {
        if (n == 0)
            break;
 
        a.clear();
        vector<int> vals(n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &vals[i]);
        NotFoundAns = false;
 
        rec(n, vals, 1, n);
 
        if (NotFoundAns) {
            printf("-1\n");
        } else {
            printf("%d\n", (int)a.size());
            for (auto &i : a)
                printf("%d %d\n", i.first, i.second);
        }
    }
 
    return 0;
}
