#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 3;
int x = 0;

// wait operation
void wait() {
    mutex--;
}

// signal operation
void signal() {
    mutex++;
}

// producer
void producer() {
    if ((mutex == 1) && (empty != 0)) {
        wait();
        full++;
        empty--;
        x++;
        printf("Producer has produced: Item %d\n", x);
        signal();
    } else {
        printf("Buffer is full!\n");
    }
}

// consumer
void consumer() {
    if ((mutex == 1) && (full != 0)) {
        wait();
        full--;
        empty++;
        printf("Consumer has consumed: Item %d\n", x);
        x--;
        signal();
    } else {
        printf("Buffer is empty!\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
