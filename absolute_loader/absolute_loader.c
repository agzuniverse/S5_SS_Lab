#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *fp;
    int addr, staddri;
    char line[50], staddr[10];
    fp = fopen("object_code.txt", "r");
    fscanf(fp, "%s", line);
    while (!feof(fp))
    {
        fscanf(fp, "%s", line);
        if (line[0] == 'T')
        {
            int i = 0, j = 0;
            for (i = 2, j = 0; i < 8; i++, j++)
                staddr[j] = line[i];
            staddr[j] = '\0';
            staddri = atoi(staddr);
            i = 12;
            while (line[i] != '$')
            {
                if (line[i] != '^')
                {
                    printf("00%d %c%c\n", staddri, line[i], line[i + 1]);
                    staddri++;
                    i += 2;
                }
                else
                    i++;
            }
        }
        else if (line[0] == 'E')
            break;
    }
}