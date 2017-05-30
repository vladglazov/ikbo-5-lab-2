#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
typedef struct LISTS *LISTP;
typedef struct MEMLISTS *MEMLISTP;
struct LISTS
{
    unsigned char value;
    LISTP llist;
    LISTP rlist;
};
typedef enum {NONE, LEFT, RIGHT, INC, DEC, PRINT, GET, PRINTC, BEGIN, END, COMMENT} COMMAND;
struct MEMLISTS
{
    int index;
    COMMAND command;
    MEMLISTP llist;
    MEMLISTP rlist;
};
LISTP AddCell();
MEMLISTP AddList();
COMMAND GetCommand(char[MAX]);
void GoToBegin(int index, MEMLISTP *stack);
void DoCommands(LISTP*, MEMLISTP*);
void FreeBuf(MEMLISTP *buf);

int main(int argc, char *argv[])
{
    LISTP cellp = AddCell();
    MEMLISTP commands=NULL,NewEl=NULL;
    char string[MAX];
    char fname[MAX];
    COMMAND command;

    FILE *fp = NULL;
    if (argc == 2) fp = fopen (argv[1],"r");
    if (fp == NULL)
        do
        {
            printf("Enter correct file name: ");
            scanf("%s",fname);
            fp = fopen(fname, "r");
        }
        while (!fp);
    while (!feof(fp))
    {
        fscanf(fp,"%s ", string);
        command = GetCommand(string);
        if (command!=NONE)
        {
            NewEl=AddList();
            if (commands) commands->rlist=NewEl;
            NewEl->llist=commands;
            commands=NewEl;
            commands->command=command;
        }
    }
    while(commands->llist)commands=commands->llist;
    while(commands){NewEl=commands; DoCommands(&cellp,&commands);commands=commands->rlist;}
    FreeBuf(&NewEl);
    putchar('\n');
    putchar('\n');
    while ((cellp->llist)!=NULL) cellp=cellp->llist;
    while ((cellp->rlist!=NULL))
    {
        printf("%d\t", cellp->value);
        cellp=cellp->rlist;
        free(cellp->llist);
    }
    printf("%d\t", cellp->value);
    free(cellp);
    putchar('\n');
    fclose(fp);
    fflush(stdin);
    printf("Press any key");
    getchar();
    return 0;
}
LISTP AddCell()
{
    LISTP pointer = (LISTP) malloc (sizeof (struct LISTS));
    pointer->value = 0;
    pointer->rlist = NULL;
    pointer->llist = NULL;
    return pointer;
}
MEMLISTP AddList()
{
    MEMLISTP pointer;
    pointer = (MEMLISTP) malloc (sizeof (struct MEMLISTS));
    if (pointer)
    {
        pointer->index = -1;
        pointer->command = NONE;
        pointer->rlist = NULL;
        pointer->llist = NULL;
    }
    return pointer;
}
COMMAND GetCommand(char string[MAX])
{

    COMMAND com = NONE;
        if (strstr(string, "movl")) com = LEFT;
        if (strstr(string, "movr")) com = RIGHT;
        if (strstr(string, "inc")) com = INC;
        if (strstr(string, "dec")) com = DEC;
        if (strstr(string, "print")) com = PRINT;
        if (strstr(string, "get")) com = GET;
        if (strstr(string, "printc")) com = PRINTC;
        if (strstr(string, "begin")) com = BEGIN;
        if (strstr(string, "end")) com = END;
        if (strstr(string, "*")) com = COMMENT;
    return com;
}
void DoCommands(LISTP* cellp, MEMLISTP *commands)
{
    static int i = -1;
    switch ((*commands)->command)
    {
    case LEFT:
    if ((*cellp)->llist==NULL)
    {
        (*cellp)->llist= AddCell();
        (*cellp)->llist->rlist=(*cellp);
    }
    (*cellp)=(*cellp)->llist;
    break;
    case RIGHT:
    if ((*cellp)->rlist==NULL)
    {
        (*cellp)->rlist= AddCell();
        (*cellp)->rlist->llist=(*cellp);
    }
    (*cellp)=(*cellp)->rlist;
    break;
    case INC:
    if ((*cellp)->value==MAX)
    {
        printf("Warning! Max value\n");
        (*cellp)->value = 0;
    }
    else
    (*cellp)->value++;
    break;
    case DEC:
    if ((*cellp)->value != 0)(*cellp)->value--;
    break;
    case PRINT:
    printf("%d ",(*cellp)->value);
    break;
    case GET:
    printf("Enter symbol: ");
    fflush(stdin);(*cellp)->value = getchar();
    break;
    case PRINTC:
    printf("%c ",(*cellp)->value);
    break;
    case BEGIN:
    (*commands)->index=++i;
    break;
    case END:
    if ((*commands)->index==-1)(*commands)->index=i-1;
    if ((*cellp)->value!=0) GoToBegin(i,commands);
    else i--;
    break;
    case COMMENT:
    case NONE:
    break;
    }
}
void GoToBegin(int index, MEMLISTP *stack)
{
    do
    {
    (*stack)=(*stack)->llist;}
    while (!(((*stack)->command == BEGIN)&&((*stack)->index==index)));
}
void FreeBuf(MEMLISTP *stack)
{
    while ((*stack)->llist!=NULL)
    {
        (*stack)=(*stack)->llist;
        free((*stack)->rlist);
        (*stack)->rlist=NULL;
    }
    free(*stack);
    (*stack)=NULL;
}
