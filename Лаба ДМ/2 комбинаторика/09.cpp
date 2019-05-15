#include <bits/stdc++.h>
 
using namespace std;
 
void rec(vector<int> &a, int n, int balance = 0) {
    if (balance < 0)
        return;
    if ((int)a.size() == n) {
        if (balance != 0)
            return;
 
        for (int i : a)
            printf("%c", (char)(i + '('));
        printf("\n");
        return;
    }
 
    a.push_back(0);
    rec(a, n, balance + 1);
    a.pop_back();
    a.push_back(1);
    rec(a, n, balance - 1);
    a.pop_back();
}
 
int main() {
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    vector<int> a;
    rec(a, 2 * n);
 
    return 0;
}
