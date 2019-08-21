#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node
{
    char name[128];
    bool isDir;
    struct node *p;
    struct node *c[100];
    int i;
} * head, *curr;

void ls()
{
    if (curr->i == 0)
    {
        printf("Empty folder\n");
        return;
    }
    for (int i = 0; i < curr->i; i++)
    {
        if (curr->c[i]->isDir)
            printf("*%s*  ", curr->c[i]->name);
        else
            printf("%s  ", curr->c[i]->name);
    }
}

void touch(bool d)
{
    printf("Enter filename\n");
    char fname[128];
    scanf("%s", fname);
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->name, fname);
    temp->isDir = d;
    temp->p = curr;
    curr->c[curr->i] = temp;
    curr->i = (curr->i) + 1;
}

void cd()
{
}

void cdup()
{
}

void rmdir()
{
}

void rm()
{
}

void main()
{
    int in;
    head = (struct node *)malloc(sizeof(struct node));
    strcpy(head->name, "root");
    head->isDir = true;
    head->p = NULL;
    head->i = 0;
    curr = head;
    while (true)
    {
        printf("\n\nYou are in %s directory.\nEnter 1 to show everything in this directory\nEnter 2 to change directory\nEnter 3 to go to parent directory\nEnter 4 to add new file\nEnter 5 to delete file\nEnter 6 to create new directory\nEnter 7 to delete directory\nEnter anything else to exit\n", curr->name);
        scanf("%d", &in);
        switch (in)
        {
        case 1:
            ls();
            break;
        case 2:
            cd();
            break;
        case 3:
            cdup();
            break;
        case 4:
            touch(false);
            break;
        case 5:
            rm();
            break;
        case 6:
            touch(true);
            break;
        case 7:
            rmdir();
            break;
        default:
            exit(0);
        }
    }
}