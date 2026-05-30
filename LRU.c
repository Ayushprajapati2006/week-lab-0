#include <stdio.h>

int main()
{
    int pages[50], frames[10], time[10];
    int n, f, i, j, pos, pageFaults = 0;
    int count = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            pos = 0;

            for(j = 1; j < f; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            frames[pos] = pages[i];
            count++;
            time[pos] = count;
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);

    return 0;
}