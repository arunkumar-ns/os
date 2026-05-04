#include <stdio.h>
#include <stdlib.h>

int n, hungry;
int pos[10];

void one_at_a_time() {
    printf("Allow one philosopher to eat at any time\n");
    for (int i = 0; i < hungry; i++) {
        for (int j = i; j < hungry; j++) {
            printf("P %d is waiting\n", pos[j]);
        }
        printf("P %d is granted to eat\n", pos[i]);
        printf("P %d has finished eating\n", pos[i]);
    }
}

void two_at_a_time() {
    printf("Allow two philosophers to eat at any time\n");
    int i = 0;
    while (i < hungry) {
        for (int j = i; j < hungry; j++) {
            printf("P %d is waiting\n", pos[j]);
        }
        printf("P %d is granted to eat\n", pos[i]);
        printf("P %d has finished eating\n", pos[i]);
        if (i + 1 < hungry) {
            printf("P %d is granted to eat\n", pos[i + 1]);
            printf("P %d has finished eating\n", pos[i + 1]);
        }
        i += 2;
    }
}

int main() {
    int choice;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);
    printf("How many are hungry: ");
    scanf("%d", &hungry);
    for (int i = 0; i < hungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                one_at_a_time();
                break;
            case 2:
                two_at_a_time();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

