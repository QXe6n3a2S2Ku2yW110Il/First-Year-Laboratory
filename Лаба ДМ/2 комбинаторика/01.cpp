#include <bits/stdc++.h>
 
using namespace std;
 
void toBinary(int x, int n) {
    for (int i = n - 1; i > -1; --i)
        printf("%d", ((x >> i) & 1));
    printf("\n");
}
 
int main() {
    freopen("allvectors.in", "r", stdin);
    freopen("allvectors.out", "w", stdout);
     
    int n;
    scanf("%d", &n);
 
    for (int i = 0; i < (1 << n); ++i)
        toBinary(i, n);
  
    return 0;
}
