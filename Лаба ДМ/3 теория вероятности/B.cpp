#include <stdio.h>

using namespace std;

int main() {
    freopen("shooter.in", "r", stdin);
    freopen("shooter.out", "w", stdout);
    
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    --k;
    
    double qk = 0, qSum = 0;
    for (int i = 0; i < n; ++i) {
        double p;
        scanf("%lf", &p);
        
        double q = 1 - p, qm = 1;
        for (int j = 0; j < m; ++j)
            qm *= q;
        
        if (i == k)
            qk = qm;
        
        qSum += qm;
    }
    
    printf("%.5f", qk / sum);
    
    return 0;
}
