#include <stdio.h>

int main()
{
    int n, m, i, j, k, pid;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], req[10], finish[10] = {0}, safe[10];
    int work[10], count = 0, found;

    printf("Enter number of processes\t\t--\t");
    scanf("%d", &n);

    printf("Enter number of resources\t\t--\t");
    scanf("%d", &m);

    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for P%d\n", i);

        printf("Enter allocation\t\t--\t");
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max\t\t\t--\t");
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter Available Resources --\t");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    printf("\nEnter New Request Details --\n");

    printf("Enter pid\t--\t");
    scanf("%d", &pid);

    printf("Enter Request for Resources\t--\t");
    for(i = 0; i < m; i++)
        scanf("%d", &req[i]);

    for(i = 0; i < m; i++)
    {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
        work[i] = avail[i];
    }

    while(count < n)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    printf("\nP%d is visited(", i);

                    for(j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                        printf("%d", work[j]);

                        if(j != m - 1)
                            printf(" ");
                    }

                    printf(" )");

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\nSYSTEM IS IN SAFE STATE");
        printf("\nThe Safe Sequence is -- (");

        for(i = 0; i < n; i++)
        {
            printf("P%d", safe[i]);

            if(i != n - 1)
                printf(" ");
        }

        printf(" )");
    }
    else
    {
        printf("\nSYSTEM IS NOT IN SAFE STATE");
    }

    printf("\n\nProcess\t\tAllocation\t\tMax\t\tNeed\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t\t", i);

        for(j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);

        printf("\t\t");

        for(j = 0; j < m; j++)
            printf("%d ", max[i][j]);

        printf("\t\t");

        for(j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    return 0;
}
