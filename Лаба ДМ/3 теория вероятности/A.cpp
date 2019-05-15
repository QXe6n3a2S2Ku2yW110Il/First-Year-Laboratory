#include <stdio.h>

using namespace std;

int main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
    
    int n, k;
    scanf("%d%d", &k, &n);
    
    long long sum = 0;
    while (k--) {
        int p, m;
        scanf("%d%d", &p, &m);
        
        sum += p * m;
    }
    
    printf("%.5f", sum / 100.0 / n);
    
    return 0;
}
