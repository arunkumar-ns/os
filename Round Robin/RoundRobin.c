#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int completed;
} Process;

int main() {
    int n, tq;
    int i, time = 0, count = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Sort processes by arrival time (for scheduling only)
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    queue[rear++] = 0;  // enqueue first process
    visited[0] = 1;
    time = p[0].at;

    printf("\nGantt Chart:\n|");

    while (count < n) {
        int idx = queue[front++];
        front %= MAX;

        if (p[idx].rt > tq) {
            printf(" P%d (%d-%d) |", p[idx].pid, time, time + tq);
            time += tq;
            p[idx].rt -= tq;
        } else {
            printf(" P%d (%d-%d) |", p[idx].pid, time, time + p[idx].rt);
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].completed = 1;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            count++;
        }

        // Enqueue newly arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && !p[i].completed) {
                queue[rear++] = i;
                rear %= MAX;
                visited[i] = 1;
            }
        }

        // If current process still has remaining time, enqueue it again
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
            rear %= MAX;
        }

        // If queue empty and some processes are not completed yet, move time to next arrival
        if (front == rear) {
            for (i = 0; i < n; i++) {
                if (!p[i].completed && !visited[i]) {
                    queue[rear++] = i;
                    rear %= MAX;
                    visited[i] = 1;
                    time = p[i].at;
                    break;
                }
            }
        }
    }

    // Sort back by PID to print results in order P1, P2, ...
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].pid > p[j].pid) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate averages
    float avg_tat = 0, avg_wt = 0;

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);

    return 0;
}
