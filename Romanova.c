#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
typedef struct LISTS *LISTP;
typedef struct MEMLISTS *MEMLISTP;
struct LISTS    //MT cell
{
    unsigned char value; //for values 0-255
    LISTP llist;
    LISTP rlist;
};
typedef enum {NONE, LEFT, RIGHT, INC, DEC, PRINT, GET, PRINTC, BEGIN, END, COMMENT} COMMAND; //список команд
struct MEMLISTS //Хранит команды циклов
{
    int index;
    COMMAND command;
    MEMLISTP llist;
    MEMLISTP rlist;
};
LISTP AddCell();//Добавление памяти под ячейку ленты
MEMLISTP AddList();//Добавление памяти под хранение команд
COMMAND GetCommand(char[MAX]);//Преобразование команды
void GoToBegin(int index, MEMLISTP *stack);//В начало списка команд
void DoCommands(LISTP*, MEMLISTP*);//Выполнение команды
void FreeBuf(MEMLISTP *buf);//Освобождение списка

int main(int argc, char *argv[])
{
    LISTP cellp = AddCell();
    MEMLISTP commands=NULL,NewEl=NULL;
    char string[MAX];
    char fname[MAX];
    COMMAND command;

    FILE *fp = NULL;
    if (argc == 2) fp = fopen (argv[1],"r");
    if (fp == NULL);
        do
        {
            printf("Enter correct file name: ");
            scanf("%s",&fname);
        }
        while (!(fp = fopen(fname, "r")));
    while (!feof(fp))
    {
        fscanf(fp,"%s ", &string);//Чтение команд из файла
        if ((command = GetCommand(string))!=NONE)//Если не пустая команда
        {
            NewEl=AddList();
            if (commands) commands->rlist=NewEl;
            NewEl->llist=commands;
            commands=NewEl;
            commands->command=command;//Записываем команду в список
        }
    }
    while(commands->llist)commands=commands->llist;//Двигаемся в начало
    while(commands){NewEl=commands; DoCommands(&cellp,&commands);commands=commands->rlist;}//Выполняем команды из буфера
    FreeBuf(&NewEl);//Освобождаем память
    putchar('\n');
    putchar('\n');
    while ((cellp->llist)!=NULL) cellp=cellp->llist;//вывод результирующей ленты
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
    return 0;
}
LISTP AddCell()//Добавление ячейки
{
    LISTP pointer = (LISTP) malloc (sizeof (struct LISTS));
    pointer->value = 0;
    pointer->rlist = NULL;
    pointer->llist = NULL;
    return pointer;
}
MEMLISTP AddList()//Добавление в список, где хранятся данные о циклах
{
    MEMLISTP pointer;
    if (pointer = (MEMLISTP) malloc (sizeof (struct MEMLISTS)))
    pointer->index = -1;
    pointer->command = NONE;
    pointer->rlist = NULL;
    pointer->llist = NULL;
    return pointer;
}
COMMAND GetCommand(char string[MAX]) //Преобразует команду
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
void DoCommands(LISTP* cellp, MEMLISTP *commands) //Выполняет команду
{
    static int i=-1;//Для индексации цикла
    switch ((*commands)->command)
    {
    case LEFT://Двигаемся влево
    if ((*cellp)->llist==NULL)
    {
        (*cellp)->llist= AddCell();
        (*cellp)->llist->rlist=(*cellp);
    }
    (*cellp)=(*cellp)->llist;//Сдвигаем указатель
    break;
    case RIGHT: //Двигаеся вправо
    if ((*cellp)->rlist==NULL) //Если справа нет ячейки, добавляем
    {
        (*cellp)->rlist= AddCell();
        (*cellp)->rlist->llist=(*cellp);
    }
    (*cellp)=(*cellp)->rlist;//Сдвигаем указатель
    break;
    case INC:
    if ((*cellp)->value==MAX)//Если 255
    {
        printf("Warning! Max value\n");//Предупреждение
        (*cellp)->value = 0;//Обнуление
    }
    else
    (*cellp)->value++; //Прибавление
    break;
    case DEC://Вычитание
    if ((*cellp)->value != 0)(*cellp)->value--;//Если есть что вычитать
    break;
    case PRINT:
    printf("%d ",(*cellp)->value);//Выводим как число
    break;
    case GET:
    printf("Enter symbol: ");
    fflush(stdin);(*cellp)->value = getchar();//Чтение с клавиатуры
    break;
    case PRINTC:
    printf("%c ",(*cellp)->value);//ыводим как символ
    break;
    case BEGIN:
    (*commands)->index=++i; //Индексируем элементы цикла чтобы в дальнейшем возвращаться
    break;
    case END:
    if ((*commands)->index==-1)(*commands)->index=i-1;//Индексируем
    if ((*cellp)->value!=0) GoToBegin(i,commands);
    else i--;
    break;
    case COMMENT:
    case NONE:
    break;
    }
}
void GoToBegin(int index, MEMLISTP *stack)//Возврат в бегин с нужным индексом
{
    do
    {
    (*stack)=(*stack)->llist;}
    while (!(((*stack)->command == BEGIN)&&((*stack)->index==index)));
}
void FreeBuf(MEMLISTP *stack) //Освобождение памяти
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
