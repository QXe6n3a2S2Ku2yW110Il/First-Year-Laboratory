#include <stdio.h>
#include <vector>
#include <string>
 
using namespace std;
 
int main() {
    string sameCode[] = {"Unko", "VOlP"};
 
    int n;
    scanf("%d", &n);
 
    int upPow2 = 1;
    while (upPow2 < n)
        upPow2 *= 2;
 
    int log2n = 0;
    for (int i = 0; i < 31; ++i) {
        if (((upPow2 >> i) & 1) == 1)
            log2n = i;
    }
 
    while (n--) {
        for (int currBit = 0; currBit < log2n; ++currBit)
            printf("%s", sameCode[(n >> currBit) & 1].c_str());
        printf("\n");
    }
 
    return 0;
}
