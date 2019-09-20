#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int n;
    printf("Enter the max size of the buffer\n");
    scanf("%d", &n);
    int buffer[n];
    int i = -1;
    int c;
    do
    {
        printf("\nChoose:\n1.Produce\n2.Consume\n3.Exit\n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            if (i < n - 1)
            {
                int data;
                printf("Enter data to produce\n");
                scanf("%d", &data);
                i++;
                buffer[i] = data;
            }
            else
                printf("Semaphore is full!\n");
            break;
        case 2:
            if (i >= 0)
            {
                printf("Data consumed is %d\n", buffer[i]);
                i--;
            }
            else
                printf("Semaphore is empty!\n");
            break;
        default:
            exit(0);
        }
    } while (c < 3);
}