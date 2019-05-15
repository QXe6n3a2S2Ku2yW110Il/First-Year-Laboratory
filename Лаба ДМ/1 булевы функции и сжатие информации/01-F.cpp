#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
int main() {
    int n;
    cin >> n;
    n = (1 << n);
 
    vector<string> args(n);
    vector<vector<int>> triangle(n, vector<int>(n));
 
    for (int i = 0; i < n; ++i)
        cin >> args[i] >> triangle[i][0];
 
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            triangle[i][j] = (triangle[i][j - 1] + triangle[i + 1][j - 1]) % 2;
        }
    }
 
    for (int i = 0; i < n; ++i)
        cout << args[i] << ' ' << triangle[0][i] << '\n';
 
    return 0;
}
