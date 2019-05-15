#include <stdio.h>
#include <vector>
 
using namespace std;
 
struct cashbox {
    int wait = 0, time = 0;
 
    cashbox() = default;
    cashbox(int a, int b): wait(a), time(b) {}
};
 
int n, p;
vector<cashbox> cashier;
 
bool enough(long long t) {
    vector<int> purchases(p);
    for (auto &i : cashier) {
        if (i.time == 0) {
            if (i.wait > t)
                continue;
            return true;
        }
        // i.time > 0
        long long curr_p = (t - i.wait) / i.time;
        if (curr_p < 0)
            continue;
        if (curr_p >= p)
            return true;
 
        ++purchases[curr_p];
    }
 
    int curr_qty = p - 1, left = n, cakes = 0;
    while (curr_qty > 0 && left > 0) {
        while (purchases[curr_qty] > 0 && left > 0) {
            cakes += curr_qty;
            --purchases[curr_qty];
            --left;
        }
        --curr_qty;
    }
 
    return cakes >= p;
}
 
long long bin_search() {
    long long left = -1, right = (long long)1e10;
    while (right - left > 1) {
        long long middle = left + (right - left) / 2;
        if (enough(middle))
            right = middle;
        else
            left = middle;
    }
 
    return right;
}
 
int main() {
    int m;
    scanf("%d", &m);
 
    cashier.resize(m);
    for (int i = 0; i < m; ++i) {
        int b;
        scanf("%d%d%d", &cashier[i].time, &b, &cashier[i].wait);
        cashier[i].wait += b;
    }
    scanf("%d%d", &n, &p);
 
    printf("%I64d", bin_search());
 
    return 0;
}
