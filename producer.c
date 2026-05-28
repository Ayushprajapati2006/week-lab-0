#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

HANDLE mutex;

// Producer function
DWORD WINAPI producer(LPVOID arg)
{
    int item;

    for (int i = 0; i < 10; i++)
    {
        item = rand() % 100;

        WaitForSingleObject(mutex, INFINITE);

        if (count < BUFFER_SIZE)
        {
            buffer[in] = item;
            printf("Produced: %d\n", item);

            in = (in + 1) % BUFFER_SIZE;
            count++;
        }

        ReleaseMutex(mutex);

        Sleep(1000);
    }

    return 0;
}

// Consumer function
DWORD WINAPI consumer(LPVOID arg)
{
    int item;

    for (int i = 0; i < 10; i++)
    {
        WaitForSingleObject(mutex, INFINITE);

        if (count > 0)
        {
            item = buffer[out];
            printf("Consumed: %d\n", item);

            out = (out + 1) % BUFFER_SIZE;
            count--;
        }

        ReleaseMutex(mutex);

        Sleep(1000);
    }

    return 0;
}

int main()
{
    HANDLE prodThread, consThread;

    mutex = CreateMutex(NULL, FALSE, NULL);

    prodThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    CloseHandle(prodThread);
    CloseHandle(consThread);
    CloseHandle(mutex);

    return 0;
}