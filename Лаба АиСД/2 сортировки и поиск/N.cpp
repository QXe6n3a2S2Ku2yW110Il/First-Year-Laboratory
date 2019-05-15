#include <stdio.h>
 
using namespace std;
 
void OddEvenSN(int n) {
    if (n == 1) {
        printf("1 0 0");
        return;
    }
    if (n == 2) {
        printf("2 1 1\n1 1 2");
        return;
    }
 
    int qty;
    if (n % 2 == 0)
        qty = (n - 1) * n / 2;
    else
        qty = n / 2 * n;
    printf("%d %d %d\n", n, qty, n);
 
    if (n % 2 == 0) {
        for (int i = 0; i < n / 2; ++i) {
            printf("%d ", n / 2);
            for (int j = 1; j < n; j += 2)
                printf("%d %d ", j, j + 1);
            printf("\n%d ", n / 2 - 1);
            for (int j = 2; j < n; j += 2)
                printf("%d %d ", j, j + 1);
            printf("\n");
        }
    } else {
        for (int i = 0; i < n / 2; ++i) {
            printf("%d ", n / 2);
            for (int j = 1; j < n; j += 2)
                printf("%d %d ", j, j + 1);
            printf("\n%d ", n / 2);
            for (int j = 2; j < n; j += 2)
                printf("%d %d ", j, j + 1);
            printf("\n");
        }
        printf("%d ", n / 2);
        for (int j = 1; j < n; j += 2)
            printf("%d %d ", j, j + 1);
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    if (n <= 12) {
        OddEvenSN(n);
        return 0;
    }
 
    if (n == 13) {
        printf("13 45 10\n");
        printf("6 1 6 9 13 2 8 4 10 3 5 7 12\n");
        printf("6 1 7 8 10 2 4 6 12 3 9 5 13\n");
        printf("5 1 3 5 6 7 9 10 11 12 13\n");
        printf("4 8 9 11 13 6 10 4 12\n");
        printf("5 2 6 10 12 3 4 5 8 9 11\n");
        printf("4 1 2 6 7 9 10 11 12\n");
        printf("5 4 7 3 6 2 5 8 9 10 11\n");
        printf("4 4 8 2 3 5 6 7 9\n");
        printf("4 3 5 7 8 4 6 9 10\n");
        printf("2 4 5 6 7");
    }
 
    if (n == 16) {
        printf("16 60 10\n");
        printf("8 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\n");
        printf("8 2 4 6 8 10 12 14 16 1 3 5 7 9 11 13 15\n");
        printf("8 4 8 12 16 3 7 11 15 2 6 10 14 1 5 9 13\n");
        printf("8 8 16 7 15 6 14 5 13 4 12 3 11 2 10 1 9\n");
        printf("7 6 11 7 10 4 13 8 12 14 15 2 3 5 9\n");
        printf("4 2 5 8 14 3 9 12 15\n");
        printf("6 3 5 6 7 10 11 12 14 4 9 8 13\n");
        printf("4 7 9 4 6 8 10 11 13\n");
        printf("5 4 5 6 7 8 9 10 11 12 13\n");
        printf("2 7 8 9 10");
    }
 
    if (n == 15) {
        printf("15 56 10\n");
        printf("7 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n");
        printf("7 2 4 6 8 10 12 1 3 5 7 9 11 13 15\n");
        printf("7 4 8 3 7 11 15 2 6 10 14 1 5 9 13\n");
        printf("7 7 15 6 14 5 13 4 12 3 11 2 10 1 9\n");
        printf("7 6 11 7 10 4 13 8 12 14 15 2 3 5 9\n");
        printf("4 2 5 8 14 3 9 12 15\n");
        printf("6 3 5 6 7 10 11 12 14 4 9 8 13\n");
        printf("4 7 9 4 6 8 10 11 13\n");
        printf("5 4 5 6 7 8 9 10 11 12 13\n");
        printf("2 7 8 9 10");
    }
 
    if (n == 14) {
        printf("14 51 10\n");
        printf("7 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n");
        printf("6 2 4 6 8 10 12 1 3 5 7 9 11\n");
        printf("6 4 8 3 7 2 6 10 14 1 5 9 13\n");
        printf("6 6 14 5 13 4 12 3 11 2 10 1 9\n");
        printf("6 6 11 7 10 4 13 8 12 2 3 5 9\n");
        printf("3 2 5 8 14 3 9\n");
        printf("6 3 5 6 7 10 11 12 14 4 9 8 13\n");
        printf("4 7 9 4 6 8 10 11 13\n");
        printf("5 4 5 6 7 8 9 10 11 12 13\n");
        printf("2 7 8 9 10");
    }
 
    return 0;
}
