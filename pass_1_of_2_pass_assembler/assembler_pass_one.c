#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    FILE *inp,*optab,*symtab,*f4;
    int locctr,starting_addr,l,operand,o,len;
    char opcode[20],label[20],op[20],opcode_from_optable[20];
    inp=fopen("inp.txt","r");
    symtab=fopen("symtab.txt","w");
    fscanf(inp,"%s %s %d",label,opcode,&operand);
    if(strcmp(opcode,"START")==0)
    {
        starting_addr=operand;
        locctr=starting_addr;
        printf("\t%s\t%s\t%d\n",label,opcode,operand);    
    }
    else
        locctr=0;
    fscanf(inp,"%s %s",label,opcode);
    while(!feof(inp))
    {
        fscanf(inp,"%s",op);
        printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,op);
        if(strcmp(label,"-")!=0)
        {
            fprintf(symtab,"\n%d\t%s\t%s\t%s\n",locctr,label,opcode,op);        
        }
        optab=fopen("optab.txt","r");
        fscanf(optab,"%s %d",opcode_from_optable,&o);
        while(!feof(optab))
        {
            if(strcmp(opcode,opcode_from_optable)==0)
            {
                locctr=locctr+3;
                break;    
            }
            fscanf(optab,"%s %d",opcode_from_optable,&o);
        }    
        fclose(optab);
        if(strcmp(opcode,"WORD")==0)
        {
            locctr=locctr+3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            operand=atoi(op);
            locctr=locctr+(3*operand);
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            if(op[0]=='X')
                locctr=locctr+1;
            else
            {
                len=strlen(op)-3;
                locctr=locctr+len;
            }        
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            operand=atoi(op);
            locctr=locctr+operand;
        }
        fscanf(inp,"%s%s",label,opcode);
    }
    if(strcmp(opcode,"END")==0)
    {
        printf("\nProgram Length = %d",locctr-starting_addr);
    }
    fclose(inp);
    fclose(symtab);
}