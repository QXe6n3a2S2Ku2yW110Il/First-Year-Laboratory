#include <stdio.h>
#include <algorithm>

using namespace std;

int n, m;

void crutch() {
    for (int i = 2; i <= m; ++i)
        printf("1 1 %d\n", i);
    printf("0 %d %d", max(1, m - 1), m);
    exit(0);
}

void writeTest(int a, int b, int c) {
    printf("%d %d %d\n", a, b, c);
    --m;
}

int main() {
    scanf("%d%d", &n, &m);

    if (m <= 3)
        crutch();

    writeTest(1, 3, 1);
    writeTest(1, 3, 2);

    for (int create = 3; m > 0; ++create) {
        writeTest(1, create + 1, create);

        int destroy = 2 - create % 2;
        for (; destroy < create - 1 && m > 0; destroy += 2)
            writeTest(0, destroy, destroy + 1);
    }

    return 0;
}
