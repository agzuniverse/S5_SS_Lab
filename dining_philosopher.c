#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool all_philosophers_finished_eating(bool phils[], int n)
{
    for (int i = 0; i < n; i++)
        if (!phils[i])
            return false;
    return true;
}

void clear_chopsticks(bool chops[], int n)
{
    for (int i = 0; i < n; i++)
        chops[i] = true;
}

int main()
{
    printf("Enter number of philosophers\n");
    int n;
    scanf("%d", &n);
    bool chops[n];
    bool philosophers_finished_eating[n];
    clear_chopsticks(chops, n);

    bool flag = true;
    while (flag)
    {
        printf("\nNew loop:\n");
        clear_chopsticks(chops, n);
        flag = false;
        for (int i = 0; i < n; i++)
        {
            if (!philosophers_finished_eating[i])
            {
                if (chops[i] && chops[(i + 1) % 5])
                {
                    chops[i] = false;
                    chops[(i + 1) % 5] = false;
                    printf("Philosopher %d is eating\n", i);
                    philosophers_finished_eating[i] = true;
                    flag = true;
                }
                else
                    printf("Philosopher %d is thinking\n", i);
            }
            else
                printf("Philosopher %d has finished eating\n", i);
        }
        if (all_philosophers_finished_eating(philosophers_finished_eating, n))
        {
            printf("Program completed successfully\n");
            exit(0);
        }
    }
    printf("Deadlock is present\n");
}