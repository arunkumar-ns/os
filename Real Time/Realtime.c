#include <stdio.h>
#include <limits.h>

#define MAX_TASKS 100
#define SIM_TIME 20

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
    int next_release;
    int weight;
};

// ---------------- Reset Function ----------------
void resetTasks(struct Task tasks[], int n) {
    for (int i = 0; i < n; i++) {
        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
        tasks[i].deadline = tasks[i].period;
    }
}

// ---------------- Gantt Chart ----------------
void printGanttChart(int schedule[]) {
    printf("\nGantt Chart:\n|");

    int prev = schedule[0];
    if (prev == 0) printf(" Idle |");
    else printf(" T%d |", prev);

    for (int i = 1; i < SIM_TIME; i++) {
        if (schedule[i] != prev) {
            if (schedule[i] == 0)
                printf(" Idle |");
            else
                printf(" T%d |", schedule[i]);
            prev = schedule[i];
        }
    }

    printf("\n0");

    prev = schedule[0];
    for (int i = 1; i < SIM_TIME; i++) {
        if (schedule[i] != prev) {
            printf("    %d", i);
            prev = schedule[i];
        }
    }
    printf("    %d\n", SIM_TIME);
}

// ---------------- Rate Monotonic ----------------
void rateMonotonic(struct Task tasks[], int n) {
    printf("\n===== Rate Monotonic Scheduling =====\n");

    int schedule[SIM_TIME];

    for (int time = 0; time < SIM_TIME; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].next_release += tasks[i].period;
            }
        }

        int selected = -1;
        int min_period = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            schedule[time] = tasks[selected].id;
            tasks[selected].remaining--;
        } else {
            schedule[time] = 0; // Idle
        }
    }

    printGanttChart(schedule);
}

// ---------------- EDF ----------------
void earliestDeadlineFirst(struct Task tasks[], int n) {
    printf("\n===== Earliest Deadline First =====\n");

    int schedule[SIM_TIME];

    for (int time = 0; time < SIM_TIME; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = time + tasks[i].period;
                tasks[i].next_release += tasks[i].period;
            }
        }

        int selected = -1;
        int earliest_deadline = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 && tasks[i].deadline < earliest_deadline) {
                earliest_deadline = tasks[i].deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            schedule[time] = tasks[selected].id;
            tasks[selected].remaining--;
        } else {
            schedule[time] = 0;
        }
    }

    printGanttChart(schedule);
}

// ---------------- Proportional Scheduling ----------------
void proportionalScheduling(struct Task tasks[], int n) {
    printf("\n===== Proportional Scheduling =====\n");

    int schedule[SIM_TIME];

    int current = 0;
    int slice = tasks[0].weight;

    for (int time = 0; time < SIM_TIME; time++) {

        if (slice == 0) {
            current = (current + 1) % n;
            slice = tasks[current].weight;
        }

        schedule[time] = tasks[current].id;
        slice--;
    }

    printGanttChart(schedule);
}

// ---------------- MAIN ----------------
int main() {

    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[MAX_TASKS];

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);

        tasks[i].id = i + 1;

        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution);

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        printf("DeadLine: ");
        scanf("%d", &tasks[i].weight);

        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
        tasks[i].deadline = tasks[i].period;
    }

    rateMonotonic(tasks, n);

    resetTasks(tasks, n);
    earliestDeadlineFirst(tasks, n);

    resetTasks(tasks, n);
    proportionalScheduling(tasks, n);

    return 0;
}
