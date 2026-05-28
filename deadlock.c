#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    // n = processes
    // m = resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    int finish[n];

    // Initialize finish array
    for(i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int found;

    do
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                // Check if request <= available
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                // Process can complete
                if(flag)
                {
                    for(k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;

                    printf("\nProcess P%d completed", i);
                }
            }
        }

    } while(found);

    // Check deadlock
    int deadlock = 0;

    printf("\n\nDeadlocked Processes:\n");

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
    {
        printf("No Deadlock Detected");
    }

    printf("\n");

    return 0;
}