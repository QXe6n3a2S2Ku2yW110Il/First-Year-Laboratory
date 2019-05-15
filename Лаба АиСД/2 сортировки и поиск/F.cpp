#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<int> res_mas(n + 1);
    for (int i = 1; i <= n; i++)
        res_mas[i] = i;
 
    for (int i = 3; i <= n; i++)
        swap(res_mas[(i + 1) / 2], res_mas[i]);
 
    for (int i = 1; i <= n; i++)
        printf("%d ", res_mas[i]);
 
    return 0;
}
