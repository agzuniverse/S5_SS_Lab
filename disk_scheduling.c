#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void fcfs(int *locs, int n, int start)
{
    int seek_distance = 0;
    seek_distance += abs(start - locs[0]);
    for (int i = 1; i < n; i++)
        seek_distance += abs(locs[i] - locs[i - 1]);
    printf("Average movement of head using FCFS: %.3f\n", (float)seek_distance / n);
}

void scan(int *locs, int n, int start, int max)
{
    int seek_distance = 0;
    int *temp = locs;
    qsort(temp, n, sizeof(int), cmpfunc);
    if (temp[0] > start)
        printf("Average movement of head using SCAN: %.3f\n", (float)(abs(temp[n - 1] - start) / n));
    else
        printf("Average movement of head using SCAN: %.3f\n", (float)((max - temp[0] + max - start) / n));
}

void cscan(int *locs, int n, int start, int max)
{
    int seek_distance = 0;
    int *temp = locs;
    qsort(temp, n, sizeof(int), cmpfunc);
    if (temp[0] > start)
        printf("Average movement of head using C-SCAN: %.3f\n", (float)(abs(temp[n - 1] - start) / n));
    else
    {
        int i;
        for (i = 0; i < n; i++)
            if (locs[i] > start)
                break;
        i -= 1;
        printf("Average movement of head using C-SCAN: %.3f\n", (float)((max - start + max + locs[i]) / n));
    }
}

void main()
{
    printf("Enter number of locations\n");
    int n;
    scanf("%d", &n);
    printf("Enter starting location of head\n");
    int start;
    scanf("%d", &start);
    printf("Enter maximum possible location index\n");
    int max;
    scanf("%d", &max);
    printf("Enter the %d locations on the disk to access data from\n", n);
    int locs[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", locs + i);
        if (*(locs + i) > max)
        {
            printf("ERROR: Location greater than maximum location possible\n");
            return;
        }
    }
    fcfs(locs, n, start);
    scan(locs, n, start, max);
    cscan(locs, n, start, max);
}