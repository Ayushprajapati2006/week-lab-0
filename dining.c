#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE forks[N];

DWORD WINAPI philosopher(LPVOID num)
{
    int id = *(int*)num;

    while(1)
    {
        printf("Philosopher %d is thinking\n", id);
        Sleep(1000);

        // Pick left fork
        WaitForSingleObject(forks[id], INFINITE);
        printf("Philosopher %d picked left fork %d\n", id, id);

        // Pick right fork
        WaitForSingleObject(forks[(id + 1) % N], INFINITE);
        printf("Philosopher %d picked right fork %d\n", id, (id + 1) % N);

        // Eating
        printf("Philosopher %d is eating\n", id);
        Sleep(2000);

        // Release forks
        ReleaseMutex(forks[id]);
        ReleaseMutex(forks[(id + 1) % N]);

        printf("Philosopher %d released forks\n", id);
    }

    return 0;
}

int main()
{
    HANDLE philosophers[N];
    int ids[N];

    int i;

    // Create mutexes
    for(i = 0; i < N; i++)
    {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    // Create threads
    for(i = 0; i < N; i++)
    {
        ids[i] = i;
        philosophers[i] = CreateThread(
            NULL,
            0,
            philosopher,
            &ids[i],
            0,
            NULL
        );
    }

    // Wait for threads
    WaitForMultipleObjects(N, philosophers, TRUE, INFINITE);

    return 0;
}