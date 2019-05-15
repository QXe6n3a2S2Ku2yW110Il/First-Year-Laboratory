#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
const int MAX_BITS = 5;
 
bool self_dual(vector<int> &a) {
    int n = (int)a.size();
    for (int i = 0; i <= n / 2; ++i) {
        if (a[i] == a[n - 1 - i])
            return false;
    }
 
    return true;
}
 
bool all_bits_greater(int x, int y) {
    for (int i = 0; i <= MAX_BITS; ++i) {
        if (((x >> i) & 1) < ((y >> i) & 1))
            return false;
    }
 
    return true;
}
 
bool monotonous(vector<int> &a) {
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!all_bits_greater(i, j))
                continue;
            if (a[i] < a[j])
                return false;
        }
    }
 
    return true;
}
 
vector<int> Zhegalkin(vector<int> &a) {
    int n = (int)a.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        res[i][0] = a[i];
 
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            res[i][j] = (res[i][j - 1] + res[i + 1][j - 1]) % 2;
        }
    }
 
    return res[0];
}
 
int qty_ones(int x) {
    int cnt = 0;
    for (int i = 0; i <= MAX_BITS; ++i)
        cnt += ((x >> i) & 1);
     
    return cnt;
}
 
bool linear(vector<int> &a) {
    int n = (int)a.size();
    vector<int> z = Zhegalkin(a);
 
    for (int i = 0; i < n; ++i) {
        if (qty_ones(i) > 1 && z[i] == 1)
            return false;
    }
 
    return true;
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<vector<int>> funcs(n);
    for (int i = 0; i < n; ++i) {
        int args;
        scanf("%d", &args);
        for (int j = 0; j < (1 << args); ++j) {
            char c;
            scanf(" %c", &c);
             
            if (c == '0')
                funcs[i].push_back(0);
            if (c == '1')
                funcs[i].push_back(1);
        }
    }
 
    bool T0 = true, T1 = true, S = true, M = true, L = true;
    for (int i = 0; i < n; ++i) {
        if (funcs[i][0] == 1)
            T0 = false;
        if (funcs[i].back() == 0)
            T1 = false;
        if (!self_dual(funcs[i]))
            S = false;
        if (!monotonous(funcs[i]))
            M = false;
        if (!linear(funcs[i]))
            L = false;
    }
 
    if (T0 || T1 || S || M || L)
        printf("NO");
    else
        printf("YES");
 
    return 0;
}
