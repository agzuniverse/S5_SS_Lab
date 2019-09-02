#include <stdio.h>
#include <stdbool.h>

bool check_if_resources_are_enough(int *res, int res_left[], int i, int n, int r)
{
    for (int k = 0; k < r; k++)
        if (*(res + i * r + k) > res_left[k])
            return false;
    return true;
}

void bankers_algo(int *res_needed, int *res_allocated, int res_left[], int n, int r, int finished_processes)
{
    bool deadlock_present;
    while (true)
    {
        deadlock_present = true;
        for (int i = 0; i < n; i++)
        {
            if (*(res_needed + i * r) != -1 && check_if_resources_are_enough(res_needed, res_left, i, n, r))
            {
                for (int j = 0; j < r; j++)
                    res_left[j] = *(res_needed + i * r + j) + *(res_allocated + i * r + j);
                finished_processes++;
                if (finished_processes == n)
                {
                    printf("Deadlock is not present\n");
                    return;
                }
                *(res_needed + i * r) = -1;
                deadlock_present = false;
            }
        }
        if (deadlock_present)
        {
            printf("Deadlock Present!\n");
            return;
        }
    }
}

void main()
{
    printf("** Program to simulate Banker's algorithm **\n");
    int n;
    printf("Enter number of processes\n");
    scanf("%d", &n);
    int r;
    printf("Enter number of resources\n");
    scanf("%d", &r);
    int res_needed[n][r];
    int res_allocated[n][r];
    int res_left[r];
    printf("Enter resources currently NEEDED by %d processes\n", n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", (*(res_needed + i) + j));
    printf("Enter resources currently HELD by %d processes\n", n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", (*(res_allocated + i) + j));
    printf("Enter amount of resources that are left\n");
    for (int i = 0; i < r; i++)
        scanf("%d", res_left + i);
    int finished_processes = 0;
    bankers_algo(res_needed[0], res_allocated[0], res_left, n, r, finished_processes);
}