#include <stdio.h>

int main() {
    int r, c, i, j;

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    int a[r][c];
    printf("Enter matrix elements:\n");

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Row sums
    for(i = 0; i < r; i++) {
        int rowSum = 0;
        for(j = 0; j < c; j++) {
            rowSum += a[i][j];
        }
        printf("Sum of row %d = %d\n", i + 1, rowSum);
    }

    // Column sums
    for(j = 0; j < c; j++) {
        int colSum = 0;
        for(i = 0; i < r; i++) {
            colSum += a[i][j];
        }
        printf("Sum of column %d = %d\n", j + 1, colSum);
    }

    return 0;
}
