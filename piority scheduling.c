#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int priority;   // Priority (lower value = higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int rt;         // Remaining Time (for preemptive)
};

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter priority for process %d: ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt; // initialize remaining time
    }

    printf("\nChoose Scheduling Type:\n1. Non-Preemptive Priority\n2. Preemptive Priority\nEnter choice: ");
    scanf("%d", &choice);

    int time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    if (choice == 1) {
        // ---------- NON-PREEMPTIVE PRIORITY ----------
        // Sort by arrival time first, then by priority
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (p[i].at > p[j].at || 
                   (p[i].at == p[j].at && p[i].priority > p[j].priority)) {
                    struct Process temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }

        p[0].wt = 0;
        p[0].tat = p[0].bt;
        time = p[0].bt;

        for (int i = 1; i < n; i++) {
            if (time < p[i].at) time = p[i].at; // wait until arrival
            p[i].wt = time - p[i].at;
            time += p[i].bt;
            p[i].tat = p[i].wt + p[i].bt;
        }

    } else {
        // ---------- PREEMPTIVE PRIORITY ----------
        bool done[n];
        for (int i = 0; i < n; i++) done[i] = false;

        while (completed < n) {
            int idx = -1;
            int minPriority = 9999;

            // Find process with highest priority among arrived ones
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !done[i] && p[i].rt > 0) {
                    if (p[i].priority < minPriority) {
                        minPriority = p[i].priority;
                        idx = i;
                    }
                }
            }

            if (idx != -1) {
                p[idx].rt--;
                time++;
                if (p[idx].rt == 0) {
                    completed++;
                    p[idx].tat = time - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;
                    done[idx] = true;
                }
            } else {
                time++; // idle if no process has arrived
            }
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
