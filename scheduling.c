#include <stdio.h>

float calcAvg(int a[], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
        total += a[i];
    return (float)total / n;
}

int find_shortest_job(int burst[], int arrival[], int n)
{
    int min = 0;
    int min_burst = burst[0];
    for (int i = 1; i < n; i++)
    {
        if (arrival[i] == 0 && burst[i] < min_burst)
        {
            min = i;
            min_burst = burst[i];
        }
    }
    return min;
}

void printDetails(int waiting[], int burst[], int n)
{
    printf("Waiting times: ");
    for (int i = 0; i < n; i++)
        printf("%d ", waiting[i]);
    printf("\nAverage waiting time is %.2f\n", calcAvg(waiting, n));
    int turnaround[n];
    printf("Turnaround times: ");
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = burst[i] + waiting[i];
        printf("%d ", turnaround[i]);
    }
    printf("\nAverage turnaround time is %.2f\n", calcAvg(turnaround, n));
}

void cpu_cycle(int burst[], int waiting[], int arrival[], int process_in_cpu, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i != process_in_cpu && arrival[i] == 0)
            waiting[i]++;

        else if (i != process_in_cpu && arrival[i] > 0)
            arrival[i]--;
    }
    burst[process_in_cpu]--;
}

void fcfs(int burst[], int arrival[], int n)
{
    int burst_backup[n];
    for (int i = 0; i < n; i++)
        burst_backup[i] = burst[i];
    int arrival_backup[n];
    for (int i = 0; i < n; i++)
        arrival_backup[i] = arrival[i];
    int waiting[n];
    for (int i = 0; i < n; i++)
        waiting[i] = 0;
    int arrival_pointer = 0;
    int process_in_cpu = -1;
    while (1)
    {
        // Wait with CPU idling
        while (arrival_backup[arrival_pointer] > 0 && process_in_cpu == -1)
        {
            arrival_backup[arrival_pointer]--;
            continue;
        }
        process_in_cpu = arrival_pointer;
        while (burst_backup[process_in_cpu] > 0)
            cpu_cycle(burst_backup, waiting, arrival_backup, process_in_cpu, n);

        arrival_backup[process_in_cpu] = -1;
        process_in_cpu = -1;
        arrival_pointer++;
        if (arrival_pointer >= n)
            break;
    }
    printDetails(waiting, burst, n);
}

void sjf(int burst[], int arrival[], int n)
{
    int burst_backup[n];
    for (int i = 0; i < n; i++)
        burst_backup[i] = burst[i];
    int arrival_backup[n];
    for (int i = 0; i < n; i++)
        arrival_backup[i] = arrival[i];
    int waiting[n];
    for (int i = 0; i < n; i++)
        waiting[i] = 0;
    int arrival_pointer = 0;
    int process_in_cpu = -1;
    while (1)
    {
        // Wait with CPU idling
        while (arrival_backup[arrival_pointer] > 0 && process_in_cpu == -1)
        {
            arrival_backup[arrival_pointer]--;
            continue;
        }
        process_in_cpu = find_shortest_job(burst, arrival_backup, n);
        while (burst_backup[process_in_cpu] > 0)
            cpu_cycle(burst_backup, waiting, arrival_backup, process_in_cpu, n);

        arrival_backup[process_in_cpu] = -1;
        process_in_cpu = -1;
        arrival_pointer++;
        if (arrival_pointer >= n)
            break;
    }
    printDetails(waiting, burst, n);
}

void round_robin(int burst[], int arrival[], int n, int tq)
{
    int burst_backup[n];
    for (int i = 0; i < n; i++)
        burst_backup[i] = burst[i];
    int arrival_backup[n];
    for (int i = 0; i < n; i++)
        arrival_backup[i] = arrival[i];
    int waiting[n];
    for (int i = 0; i < n; i++)
        waiting[i] = 0;
    int arrival_pointer = 0;
    int process_in_cpu = -1;
    while (1)
    {
        // Wait with CPU idling
        while (arrival_backup[arrival_pointer] > 0 && process_in_cpu == -1)
        {
            /* If no new processes have arrived and an existing process has burst time left,
            execute that process instead of waiting for another process to arrive */
            for (int i = 0; i < arrival_pointer; i++)
                if (burst_backup[i] > 0)
                {
                    arrival_pointer = i;
                    break;
                }
            arrival_backup[arrival_pointer]--;
            continue;
        }
        process_in_cpu = arrival_pointer;
        int cycles_used = 0;
        while (cycles_used < tq && burst_backup[process_in_cpu] > 0)
        {
            cpu_cycle(burst_backup, waiting, arrival_backup, process_in_cpu, n);
            cycles_used++;
        }
        if (burst_backup[process_in_cpu] == 0)
            arrival_backup[process_in_cpu] = -1;
        process_in_cpu = -1;
        arrival_pointer++;
        // Once all processes get a turn go back to first process
        if (arrival_pointer >= n)
            arrival_pointer = 0;
        int all_complete = 1;
        // Stop only when burst for all processes is 0
        for (int i = 0; i < n; i++)
        {
            if (burst_backup[i] > 0)
                all_complete = 0;
        }
        if (all_complete == 1)
            break;
    }
    printDetails(waiting, burst, n);
}

void priority_scheduling(int burst[], int arrival[], int n, int priorities[])
{
    int burst_backup[n];
    for (int i = 0; i < n; i++)
        burst_backup[i] = burst[i];
    int arrival_backup[n];
    for (int i = 0; i < n; i++)
        arrival_backup[i] = arrival[i];
    int waiting[n];
    for (int i = 0; i < n; i++)
        waiting[i] = 0;
    int arrival_pointer = 0;
    int process_in_cpu = -1;
    while (1)
    {
        // Wait with CPU idling
        while (arrival_backup[arrival_pointer] > 0 && process_in_cpu == -1)
        {
            arrival_backup[arrival_pointer]--;
            continue;
        }
        int highest_priority = 0;
        for (int i = 0; i < n; i++)
            if (arrival_backup[i] == 0 && priorities[i] > highest_priority)
            {
                highest_priority = priorities[i];
                process_in_cpu = i;
            }
        while (burst_backup[process_in_cpu] > 0)
            cpu_cycle(burst_backup, waiting, arrival_backup, process_in_cpu, n);

        arrival_backup[process_in_cpu] = -1;
        process_in_cpu = -1;
        arrival_pointer++;
        if (arrival_pointer >= n)
            break;
    }
    printDetails(waiting, burst, n);
}

void main()
{
    int n;
    printf("Enter number of processes\n");
    scanf("%d", &n);
    int burst[n];
    int arrival[n];

    printf("Enter burst times of %d processes\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &burst[i]);

    printf("Enter arrival times of %d processes (should be in ascending order)\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arrival[i]);

    printf("Enter time quantum (Only applicable to round robin scheduling\n");
    int time_quantum;
    scanf("%d", &time_quantum);

    printf("Enter priorities of %d processes (Only applicable to priority scheduling)\n", n);
    int priorities[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &priorities[i]);

    printf("\nUsing FCFC algorithm:\n");
    fcfs(burst, arrival, n);

    printf("\nUsing SJF algorithm\n");
    sjf(burst, arrival, n);

    printf("\nUsing Round Robin algorithm\n");
    round_robin(burst, arrival, n, time_quantum);

    printf("\nUsing priority scheduling\n");
    priority_scheduling(burst, arrival, n, priorities);
    printf("\n");
}