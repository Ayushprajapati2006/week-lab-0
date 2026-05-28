#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    // n = number of processes
    // m = number of resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
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

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], safeSeq[n];

    for(i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    for(k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    safeSeq[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("\nSystem is NOT in Safe State\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE\n");
    printf("Safe Sequence is:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d", safeSeq[i]);

        if(i != n - 1)
        {
            printf(" -> ");
        }
    }

    printf("\n");

    return 0;
}