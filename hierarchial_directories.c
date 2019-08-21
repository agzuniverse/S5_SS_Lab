#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tree
{
    char name[128];
    bool isDir;
    struct tree *adj;
    struct tree *c;
} * head, *curr;

void main()
{
    int in;
    head = (struct tree *)malloc(sizeof(struct tree));
    strcpy(head->name, "root");
    head->isDir = false;
    head->adj = NULL;
    head->c = NULL;
    curr = head;
    while (true)
    {
        printf("\n\nYou are in %s directory.\nEnter 1 to show everything in this directory\nEnter 2 to change directory\nEnter 3 to go to parent directory\nEnter 4 to add new file\nEnter 5 to delete file\nEnter 6 to create new directory\nEnter 7 to delete directory\nEnter anything else to exit\n");
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
            touch();
            break;
        case 5:
            rm();
            break;
        case 6:
            mkdir();
            break;
        case 7:
            rmdir();
            break;
        default:
            exit(0);
        }
    }
}