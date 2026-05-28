#include <stdio.h>

struct Task {
    char name[10];
    int executionTime;
    int deadline;
};

int main() {
    int n;
    printf("Earliest-Deadline First Scheduling\n");
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    for (int i = 0; i < n; i++) {
        printf("Enter name, execution time, deadline for task %d: ", i+1);
        scanf("%s %d %d", tasks[i].name, &tasks[i].executionTime, &tasks[i].deadline);
    }

    // Sort tasks by deadline (earliest deadline first)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].deadline > tasks[j].deadline) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    printf("\nExecution order (earliest deadline first):\n");
    for (int i = 0; i < n; i++) {
        printf("%s (ET=%d, Deadline=%d)\n", tasks[i].name, tasks[i].executionTime, tasks[i].deadline);
    }

    return 0;
}
