#include <stdio.h>
#include <string.h>

#define MAX 10

struct Process {
    char name[20];
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// FCFS scheduling for a queue
void FCFS(struct Process queue[], int n, int startTime) {
    int time = startTime;
    for (int i = 0; i < n; i++) {
        if (time < queue[i].arrivalTime)
            time = queue[i].arrivalTime;

        queue[i].completionTime = time + queue[i].burstTime;
        queue[i].turnaroundTime = queue[i].completionTime - queue[i].arrivalTime;
        queue[i].waitingTime = queue[i].turnaroundTime - queue[i].burstTime;

        time = queue[i].completionTime;
    }
}

// Display results
void display(struct Process queue[], int n, char type[]) {
    printf("\n%s Queue Scheduling Results:\n", type);
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               queue[i].name,
               queue[i].arrivalTime,
               queue[i].burstTime,
               queue[i].completionTime,
               queue[i].turnaroundTime,
               queue[i].waitingTime);
    }
}

int main() {
    int sysCount, userCount;
    struct Process systemQ[MAX], userQ[MAX];

    printf("Multi-Level Queue Scheduling Simulation\n");

    // Input system processes
    printf("Enter number of system processes: ");
    scanf("%d", &sysCount);
    for (int i = 0; i < sysCount; i++) {
        printf("Enter name, arrival time, burst time for system process %d: ", i+1);
        scanf("%s %d %d", systemQ[i].name, &systemQ[i].arrivalTime, &systemQ[i].burstTime);
    }

    // Input user processes
    printf("Enter number of user processes: ");
    scanf("%d", &userCount);
    for (int i = 0; i < userCount; i++) {
        printf("Enter name, arrival time, burst time for user process %d: ", i+1);
        scanf("%s %d %d", userQ[i].name, &userQ[i].arrivalTime, &userQ[i].burstTime);
    }

    // Schedule system processes first (higher priority)
    FCFS(systemQ, sysCount, 0);

    // Find last completion time of system queue
    int lastCompletion = 0;
    if (sysCount > 0)
        lastCompletion = systemQ[sysCount-1].completionTime;

    // Schedule user processes after system queue
    FCFS(userQ, userCount, lastCompletion);

    // Display results
    display(systemQ, sysCount, "System");
    display(userQ, userCount, "User");

    return 0;
}
