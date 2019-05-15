#include <iostream>
 
using namespace std;
 
const long long MAX_N = (long long)1e18;
long long realN, moveTo, x;
int m;
 
long long update0(long long x, long long to) {
    if (x <= 0)
        return x + to;
    return x;
}
 
long long askQuestion(long long q) {
    cout << "? " << q << endl;
    long long currRes;
    cin >> currRes;
 
    if (currRes == x) {
        cout << "! " << q << endl;
        exit(0);
    }
 
    return currRes;
}
 
void negativeAns() {
    cout << "! -1" << endl;
    exit(0);
}
 
void search() {
    long long lVal = x - m, rVal = x + m;
    long long rIndex = update0(x - moveTo, MAX_N);
    long long lIndex = rIndex - m;
    for (int i = 0; i < 9; ++i) {
        long long mIndex = lIndex + (rIndex - lIndex) / 2;
 
        long long Mx = askQuestion(update0(mIndex % realN, realN));
        if (Mx < lVal)
            Mx += MAX_N;
        else if (Mx > rVal)
            Mx -= MAX_N;
 
        if (Mx < x)
            lIndex = mIndex + 1;
        else
            // if (Mx > x)
            rIndex = mIndex - 1;
 
        // if (Mx == x)
        //     cout << "Pomelo";
    }
    negativeAns();
}
 
int main() {
    cin >> x >> m;
 
    realN = MAX_N - m;
    moveTo = askQuestion(realN);
 
    search();
 
    return 0;
}
