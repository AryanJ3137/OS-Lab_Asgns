#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10];
    int avail[10], need[10][10];
    int request[10];
    int finish[10], safe[10];
    int count, found, process;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

/* need matrix */ 
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);

        for(j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    count = 0;

    for(i = 0; i < n; i++)
        finish[i] = 0;

    while(count < n)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }

                if(j == m)
                {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

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
        printf("\nSystem is in Safe State\n");
        printf("Safe Sequence: ");

        for(i = 0; i < n; i++)
            printf("P%d ", safe[i] + 1);


        printf("\n\nEnter process number making request (1 to %d): ", n);
        scanf("%d", &process);


        process = process - 1;

        printf("Enter Request for P%d:\n", process + 1);

        for(j = 0; j < m; j++)
            scanf("%d", &request[j]);


        for(j = 0; j < m; j++)
        {
            if(request[j] > need[process][j])
            {
                printf("\nError: Process has exceeded its maximum claim.\n");
                return 0;
            }
        }


        for(j = 0; j < m; j++)
        {
            if(request[j] > avail[j])
            {
                printf("\nResources are not available.\n");
                return 0;
            }
        }


        for(j = 0; j < m; j++)
        {
            avail[j] -= request[j];
            alloc[process][j] += request[j];
            need[process][j] -= request[j];
        }


        for(i = 0; i < n; i++)
            finish[i] = 0;

        count = 0;

        while(count < n)
        {
            found = 0;

            for(i = 0; i < n; i++)
            {
                if(finish[i] == 0)
                {
                    for(j = 0; j < m; j++)
                    {
                        if(need[i][j] > avail[j])
                            break;
                    }

                    if(j == m)
                    {
                        for(k = 0; k < m; k++)
                            avail[k] += alloc[i][k];

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
            printf("\nRequest Granted\n");
            printf("New Safe Sequence: ");

            for(i = 0; i < n; i++)
                printf("P%d ", safe[i] + 1);
        }
        else
        {
            printf("\nRequest Cannot Be Granted\n");
        }
    }
    else
    {
        printf("\nSystem is in Unsafe State\n");
    }

    return 0;
}
