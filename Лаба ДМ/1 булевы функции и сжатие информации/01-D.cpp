#include <iostream>
#include <vector>
#include <set>
#include <string>
 
using namespace std;
 
const int MAX_BITS = 32;
const char AND_SYMB = 38, OR_SYMB = 124, NOT_SYMB = 126;
const char OPEN_BRACKET = 40, CLOSE_BRACKET = 41;
 
void negative_ans() {
    cout << "Impossible";
    exit(0);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    int n;
    cin >> n;
 
    vector<unsigned int> nums(n + 1);
    for (int i = 0; i < n + 1; ++i)
        cin >> nums[i];
     
    if (nums[n] == 0) {
        cout << "1&~1";
        return 0;
    }
     
    vector<vector<int>> table(MAX_BITS, vector<int>(n + 1));
    for (int i = 0; i < MAX_BITS; ++i) {
        for (int j = 0; j < n + 1; ++j)
            table[i][j] = ((nums[j] >> i) & 1);
    }
 
    int max_one_pos = 0, max_one_pos_f = 0;
    for (int i = 0; i < MAX_BITS; ++i) {
        for (int j = 0; j < n; ++j) {
            if (table[i][j])
                max_one_pos = max(max_one_pos, i);
        }
        if (table[i][n])
            max_one_pos_f = max(max_one_pos_f, i);
    }
    if (max_one_pos < max_one_pos_f)
        negative_ans();
 
    set<string> zeros, ones;
    for (int i = 0; i < MAX_BITS; ++i) {
        string curr_str = "";
        for (int j = 0; j < n; ++j)
            curr_str += (char)(table[i][j] + '0');
         
        if (table[i][n])
            ones.insert(curr_str);
        else
            zeros.insert(curr_str);
    }
    for (auto &i : ones) {
        if (zeros.count(i))
            negative_ans();
    }
 
    string ans = "";
    for (int i = 0; i < MAX_BITS; ++i) {
        if (!table[i][n])
            continue;
 
        ans += OPEN_BRACKET;
        for (int j = 0; j < n; ++j) {
            if (!table[i][j])
                ans += NOT_SYMB;
            ans += (char)(j + 1 + '0');
            ans += AND_SYMB;
        }
        ans.pop_back();
        ans += CLOSE_BRACKET;
        ans += OR_SYMB;
    }
    ans.pop_back();
 
    cout << ans;
 
    return 0;
}
