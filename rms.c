#include <stdio.h>

struct Task {
    char name[10];
    int executionTime;
    int period;
};

int main() {
    int n;
    printf("Rate-Monotonic Scheduling\n");
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    for (int i = 0; i < n; i++) {
        printf("Enter name, execution time, period for task %d: ", i+1);
        scanf("%s %d %d", tasks[i].name, &tasks[i].executionTime, &tasks[i].period);
    }

    // Sort tasks by period (shorter period = higher priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    printf("\nExecution order (higher priority first):\n");
    for (int i = 0; i < n; i++) {
        printf("%s (ET=%d, Period=%d)\n", tasks[i].name, tasks[i].executionTime, tasks[i].period);
    }

    return 0;
}
