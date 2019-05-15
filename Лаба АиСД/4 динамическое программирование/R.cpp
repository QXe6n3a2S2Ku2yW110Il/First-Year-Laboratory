#include <stdio.h>
#include <vector>
#include <queue>
 
using namespace std;
 
vector<vector<int>> prevSum, prevMod;
void rec(int sum, int mod) {
    if (sum == 0)
        return;
 
    rec(prevSum[sum][mod], prevMod[sum][mod]);
 
    printf("%d", sum - prevSum[sum][mod]);
}
 
int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    queue<pair<int, int>> q;
    q.push({0, 0});
    vector<vector<bool>> was(n + 10, vector<bool>(n + 10, false));
    prevSum.resize(n + 10, vector<int>(n + 10));
    prevMod.resize(n + 10, vector<int>(n + 10));
    while (!q.empty()) {
        auto tmp = q.front();
        if (tmp.first == n && tmp.second == 0)
            break;
 
        for (int i = 0; i < 10; ++i) {
            int currSum = tmp.first + i, currMod = (tmp.second * 10 + i) % n;
            if (was[currSum][currMod] || currSum > n)
                continue;
 
            was[currSum][currMod] = true;
            q.push({currSum, currMod});
            prevSum[currSum][currMod] = tmp.first;
            prevMod[currSum][currMod] = tmp.second;
        }
 
        q.pop();
    }
 
    rec(n, 0);
 
    return 0;
}
