#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct files
{
    char name[128];
    struct files *p;
} * head, *curr;

void printDirectory()
{
    if (head == NULL)
    {
        printf("No files present!\n");
        return;
    }
    struct files *temp = head;
    printf("\n");
    while (temp)
    {
        printf("|\n");
        printf("--%s\n", temp->name);
        temp = temp->p;
    }
}

void removeFile()
{
    printf("Enter filename\n");
    char fname[128];
    scanf("%s", fname);
    struct files *temp = head;
    if (strcmp(temp->name, fname) == 0)
    {
        head = temp->p;
        printf("File deleted.\n");
        return;
    }
    while (temp != NULL && temp->p != NULL)
    {
        if (strcmp(temp->p->name, fname) == 0)
        {
            temp->p = temp->p->p;
            printf("File deleted.\n");
            return;
        }
        temp = temp->p;
    }
    printf("File not found!\n");
}

void addFile()
{
    printf("Enter filename\n");
    char fname[128];
    scanf("%s", fname);
    if (curr == NULL)
    {
        curr = (struct files *)malloc(sizeof(struct files));
        strcpy(curr->name, fname);
        curr->p = NULL;
        head = curr;
        return;
    }
    struct files *temp = (struct files *)malloc(sizeof(struct files));
    strcpy(temp->name, fname);
    temp->p = NULL;
    curr->p = temp;
    curr = temp;
}

void main()
{
    int in;
    while (true)
    {
        printf("\n\nYou are in the only directory present.\nEnter 1 to show directory\nEnter 2 to add new file\nEnter 3 to delete file\nEnter anything else to exit\n");
        scanf("%d", &in);
        switch (in)
        {
        case 1:
            printDirectory();
            break;
        case 2:
            addFile();
            break;
        case 3:
            removeFile();
            break;
        default:
            exit(0);
        }
    }
}