#include <stdio.h>
 
using namespace std;
 
const double EPS = 1e-7;
 
double get_next(double &prev, double &prev2) {
    double res = 2 * prev - prev2 + 2;
    prev2 = prev;
    prev = res;
 
    return res;
}
 
bool all_h_bigger_0(int n, double prev2, double prev) {
    while ((n--)  > 2) {
        if (get_next(prev, prev2) <= EPS)
            return false;
    }
 
    return true;
}
 
double search_second_light(int n, double A) {
    double left = 0, right = A;
    for (int i = 0; i < 500; ++i) {
        double middle = (left + right) / 2;
        if (all_h_bigger_0(n, A, middle))
            right = middle;
        else
            left = middle;
    }
 
    return right;
}
 
int main() {
    int n;
    double A;
    scanf("%d%lf", &n, &A);
 
    double x = search_second_light(n, A);
    for (int i = 2; i < n; ++i)
        get_next(x, A);
 
    printf("%.2lf", x);
 
    return 0;
}
