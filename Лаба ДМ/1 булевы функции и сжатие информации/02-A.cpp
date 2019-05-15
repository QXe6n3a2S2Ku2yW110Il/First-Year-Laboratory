#include <bits/stdc++.h>
 
using namespace std;
 
pair<long long, int> get_front(queue<pair<long long, int>> &a) {
    auto res = a.front();
    a.pop();
    return res;
}
 
pair<long long, int> get_min(queue<pair<long long, int>> &a,
                             queue<pair<long long, int>> &b) {
    if (a.empty())
        return get_front(b);
    if (b.empty())
        return get_front(a);
    if (a.front() < b.front())
        return get_front(a);
    return get_front(b);
}
 
int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> frecs(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &frecs[i]);
    sort(frecs.begin(), frecs.end());
 
    queue<pair<long long, int>> p, sum;
    for (int i = 0; i < n; ++i)
        p.push({frecs[i], i});
 
    vector<int> anc(2 * n, -1);
    for (int i = 0; i < n - 1; ++i) {
        auto v1 = get_min(p, sum), v2 = get_min(p, sum);
        sum.push({v1.first + v2.first, n + i});
 
        anc[v2.second] = anc[v1.second] = n + i;
    }
 
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int curr_pos = i;
        long long curr_ans = 0;
        while (anc[curr_pos] != -1) {
            curr_pos = anc[curr_pos];
            ++curr_ans;
        }
 
        ans += curr_ans * frecs[i];
    }
 
    printf("%lld", ans);
 
    return 0;
}
