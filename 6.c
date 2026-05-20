// Simple Banker's Algorithm
#include <stdio.h>
int main()
{
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safe[n];
    // Allocation matrix
    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    // Maximum matrix
    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    // Available resources
    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }
    // Calculate Need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    // Initialize finish
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    int count = 0;
    while (count < n)
    {
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    for (k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }
                }
            }
        }
    }
    printf("Safe Sequence:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d ", safe[i]);
    }
    return 0;
}