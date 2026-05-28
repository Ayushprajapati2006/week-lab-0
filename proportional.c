#include <stdio.h>

struct Task {
    char name[10];
    int weight;
};

int main() {
    int n, totalWeight = 0;
    printf("Proportional Scheduling\n");
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    for (int i = 0; i < n; i++) {
        printf("Enter name and weight for task %d: ", i+1);
        scanf("%s %d", tasks[i].name, &tasks[i].weight);
        totalWeight += tasks[i].weight;
    }

    printf("\nCPU time share for each task:\n");
    for (int i = 0; i < n; i++) {
        double share = (double)tasks[i].weight / totalWeight * 100;
        printf("%s gets %.2f%% of CPU time\n", tasks[i].name, share);
    }

    return 0;
}
