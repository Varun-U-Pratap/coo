#include <stdio.h>
#include <stdlib.h>

void draw(int seq[], int sLen, int points[], int pLen, char *title, int total)
{
    printf("\n--- %s ---\n", title);
    for (int i = 0; i < pLen; i++)
        printf("%-6d", points[i]);
    printf("\n------------------------------------------------\n");
    for (int i = 0; i < sLen - 1; i++)
    {
        int s = -1, e = -1;
        for (int j = 0; j < pLen; j++)
        {
            if (points[j] == seq[i])
                s = j;
            if (points[j] == seq[i + 1])
                e = j;
        }
        int low = (s < e) ? s : e;
        for (int j = 0; j < low; j++)
            printf("      ");
        if (s < e)
        {
            printf("|");
            for (int j = 0; j < (e - s) * 6 - 2; j++)
                printf("-");
            printf(">");
        }
        else
        {
            printf("<");
            for (int j = 0; j < (s - e) * 6 - 2; j++)
                printf("-");
            printf("|");
        }
        printf("\n");
    }
    printf("Total Seek: %d\n", total);
}

int main()
{
    int n, head, size, req[50], p[60], pLen = 0, seq[60], sLen = 0, total = 0;
    printf("Enter n, head, disk size: ");
    scanf("%d %d %d", &n, &head, &size);
    printf("Enter %d requests: ", n);
    p[pLen++] = 0;
    p[pLen++] = head;
    p[pLen++] = size - 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
        p[pLen++] = req[i];
    }

    for (int i = 0; i < pLen; i++)
        for (int j = i + 1; j < pLen; j++)
            if (p[i] > p[j])
            {
                int t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
    int uLen = 0;
    for (int i = 0; i < pLen; i++)
        if (i == 0 || p[i] != p[i - 1])
            p[uLen++] = p[i];

    seq[0] = head;
    sLen = n + 1;
    total = 0;
    for (int i = 0; i < n; i++)
    {
        total += abs(req[i] - (i == 0 ? head : req[i - 1]));
        seq[i + 1] = req[i];
    }
    draw(seq, sLen, p, uLen, "FCFS", total);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j])
            {
                int t = req[i];
                req[i] = req[j];
                req[j] = t;
            }

    sLen = 0;
    total = 0;
    int cur = head;
    seq[sLen++] = head;
    for (int i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            total += abs(req[i] - cur);
            cur = req[i];
            seq[sLen++] = cur;
        }
    }
    total += abs((size - 1) - cur);
    cur = size - 1;
    seq[sLen++] = cur;
    for (int i = n - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            total += abs(req[i] - cur);
            cur = req[i];
            seq[sLen++] = cur;
        }
    }
    draw(seq, sLen, p, uLen, "SCAN", total);

    return 0;
}