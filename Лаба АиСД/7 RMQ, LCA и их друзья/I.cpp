#include <stdio.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <cstring>  // for memset
 
using namespace std;
 
const int K = 448, MAX_VAL = 1e6;
 
struct query {
    int left, right, index;
    query() = default;
    query(int a, int b, int c) : left(a), right(b), index(c) {}
};
 
vector<int> a;
vector<query> q;
deque<int> seg;
int cnt[MAX_VAL + 1];
long long curr_ans = 0;
 
int main() {
    memset(cnt, 0, sizeof cnt);
 
    int n, m;
    scanf("%d%d", &n, &m);
 
    a.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
 
    q.resize(m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        q[i] = query(x - 1, y - 1, i);
    }
    sort(q.begin(), q.end(), [](query &x, query &y) {
        return (x.left / K != y.left / K ? x.left < y.left : x.right < y.right);
    });
 
    int left = 0, right = -1;
    vector<long long> ans(m);
    for (int i = 0; i < m; ++i) {
        while (left > q[i].left) {
            int v = a[--left];
            curr_ans += (2LL * cnt[v] + 1) * v;
            ++cnt[v];
        }
        while (right < q[i].right) {
            int v = a[++right];
            curr_ans += (2LL * cnt[v] + 1) * v;
            ++cnt[v];
        }
        while (left < q[i].left) {
            int v = a[left++];
            --cnt[v];
            curr_ans -= (2LL * cnt[v] + 1) * v;
        }
        while (right > q[i].right) {
            int v = a[right--];
            --cnt[v];
            curr_ans -= (2LL * cnt[v] + 1) * v;
        }
 
        ans[q[i].index] = curr_ans;
    }
 
    for (auto &i : ans)
        printf("%I64d\n", i);
 
    return 0;
}
