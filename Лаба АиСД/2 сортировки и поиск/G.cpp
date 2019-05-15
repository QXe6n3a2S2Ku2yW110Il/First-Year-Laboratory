#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int HALF_MAX_INT = (1 << 16) + 7, MAX_N = 100007;
 
unsigned int genRand = 0;
int genA, genB;
unsigned int x[MAX_N], curr[MAX_N];
int cnt[HALF_MAX_INT];
 
unsigned int nextRand24() {
    genRand = genRand * genA + genB;
    return (genRand >> 8);
}
 
unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}
 
inline unsigned int get(unsigned int a, int b) {
    return ((a >> (b * 16)) & ((1 << 16) - 1));
}
 
void radixSort(int n) {
    for (int i = 0; i < n; ++i)
        x[i] = nextRand32();
 
    for (int i = 0; i < 2; ++i) {
        for (int &j : cnt)
            j = 0;
        for (int j = 0; j < n; ++j)
            ++cnt[get(x[j], i)];
 
        int count = 0;
        for (int &j : cnt) {
            int tmp = j;
            j = count;
            count += tmp;
        }
        for (int j = 0; j < n; ++j) {
            int tmp = get(x[j], i);
            curr[cnt[tmp]] = x[j];
            ++cnt[tmp];
        }
        swap(x, curr);
    }
 
    unsigned long long res = 0;
    for (int i = 0; i < n; ++i)
        res += (unsigned long long)(i + 1LL) * x[i];
    cout << res << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int test, n;
    cin >> test >> n >> genA >> genB;
 
    while (test--) {
        radixSort(n);
    }
 
    return 0;
}
