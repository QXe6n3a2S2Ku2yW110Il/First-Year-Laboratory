#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const double EPS = 1e-6, INF = 1e10;
 
int n, k;
vector<int> v, w;
 
template <typename T>
void QSort(vector<T> &a, int left, int right) {
    if (right - left <= 1)
        return;
 
    int lt = left, eq = left;
    T x = a[rand() % (right - left) + left];
    for (int i = left; i < right; ++i) {
        if (a[i] == x)
            swap(a[i], a[eq++]);
        if (a[i] < x) {
            swap(a[i], a[eq]);
            swap(a[eq++], a[lt++]);
        }
    }
 
    QSort(a, left, lt);
    QSort(a, eq, right);
}
 
bool KBestBigger(double x) {
    vector<double> bests(n);
    for (int i = 0; i < n; ++i)
        bests[i] = v[i] - x * w[i];
 
    QSort(bests, 0, n);
 
    double sum = 0;
    for (int i = n - 1; i > n - k - 1; --i)
        sum += bests[i];
 
    return sum >= EPS;
}
 
double search() {
    double left = 0, right = (int)1e7;
    for (int i = 0; i < 100; ++i) {
        double middle = left + (right - left) / 2;
        if (KBestBigger(middle))
            left = middle;
        else
            right = middle;
    }
 
    return left;
}
 
int main() {
    scanf("%d%d", &n, &k);
 
    v.resize(n);
    w.resize(n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d", &v[i], &w[i]);
 
    double best = search();
    vector<pair<double, int>> bests(n);
    for (int i = 0; i < n; ++i)
        bests[i] = {v[i] - best * w[i], i};
    QSort(bests, 0, n);
 
    for (int i = n - 1; i > n - k - 1; --i)
        printf("%d ", bests[i].second + 1);
 
    return 0;
}
