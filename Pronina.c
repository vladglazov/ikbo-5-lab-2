#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define NumOC 100 


typedef struct List1 { 
	struct List1 *Left;
	int Count;
	struct List1 *Right;
	
} List;

 long int AddCommand(char *rout, char *Commands);

int main(int argc, char *argv[]) {
	FILE *readFile;
	char rout[255], *Commands, ByteCh;
	int i = 0, flag = 0, j;
	long int NumCom = 0;
	List Word, *Pointer, *PointerBack;
	List Stack, *PointerStack, *PointerStackBack;
	if (argc>1) { 
		readFile = fopen(argv[1], "r");
		if (readFile == NULL) {
			while (1) {
				printf("Unknown file\nEnter a new file name: ");
				scanf("%s", rout);
				readFile = fopen(rout, "r");
				if (readFile != NULL)
					 break;
				
			}
			
		}
		
	}
	else while (1) { 
		printf("Enter a new file name: ");
		scanf("%s", rout);
		readFile = fopen(rout, "r");
		if (readFile != NULL)
			 break;
		printf("Unknown file\n");
		
	}
	Word.Left = NULL; Word.Right = NULL; Word.Count = 0; 
	Stack.Left = NULL; Stack.Right = NULL; Stack.Count = -1;
	Pointer = &Word; PointerStack = &Stack;
	
		Commands = (char*)malloc(NumOC * sizeof(char));
	j = NumOC;
	while (fscanf(readFile, "%s", rout) != EOF) { 
		if (NumCom == j) {
			j += NumOC;
			Commands = (char*)realloc(Commands, j);
			
		}
		NumCom = AddCommand(rout, Commands);
		
	}
	fclose(readFile);
	while (i <= NumCom) { 
		if (flag == 0) {
			if (Commands[i] == 'l') { 
				if (Pointer->Left == NULL) {
					Pointer->Left = (List*)malloc(sizeof(List));
					PointerBack = Pointer;
					Pointer = Pointer->Left;
					Pointer->Right = PointerBack;
					Pointer->Left = NULL;
					Pointer->Count = 0;
					
				}
				else
					 Pointer = Pointer->Left;
				
			}
			if (Commands[i] == 'r') { 
				if (Pointer->Right == NULL) {
					Pointer->Right = (List*)malloc(sizeof(List));
					PointerBack = Pointer;
					Pointer = Pointer->Right;
					Pointer->Left = PointerBack;
					Pointer->Right = NULL;
					Pointer->Count = 0;
					
				}
				else
					 Pointer = Pointer->Right;
				
			}
			if (Commands[i] == 'i') { 
				Pointer->Count++;
				if (Pointer->Count == 256) {
					printf("Index out of range\n");
					Pointer->Count = 0;
					
				}
				
			}
			if (Commands[i] == 'd') { 
				Pointer->Count--;
				if (Pointer->Count == -1) {
					printf("Index out of range\n");
					Pointer->Count = 0;
					
				}
				
			}
			if (Commands[i] == 't') 
				 printf("%d\n", Pointer->Count);
			if (Commands[i] == 'c')
				 printf("%c\n", Pointer->Count);
			if (Commands[i] == 'g') {
				fflush(stdin);
				scanf("%c", &ByteCh);
				fflush(stdin);
				Pointer->Count = ByteCh;
				
			}
			
		}
		if (Commands[i] == 'b') { 
			if (Pointer->Count == 0) {
				flag = 1;
				
			}
			PointerStack->Right = (List*)malloc(sizeof(List)); 
			PointerStackBack = PointerStack;
			PointerStack = PointerStack->Right;
			PointerStack->Left = PointerStackBack;
			PointerStack->Count = i;
			
		}
		if (Commands[i] == 'e') { 
			if (Pointer->Count == 0) { 
				PointerStack = PointerStack->Left;
				free(PointerStack->Right);
				flag = 0;
				
			}
			else
				 i = PointerStack->Count;
			
		}
		i++; 
		
	}
	
}

long int AddCommand(char *rout, char *Commands) { 
	static long int i = 0;
	int j = 0;
	while ((rout[j] == '/t') || (rout[j] == ' '))
		 j++;
	if (rout[j] == 'm' && rout[j + 3] == 'l')
		 Commands[i] = 'l';
	if (rout[j] == 'm' && rout[j + 3] == 'r')
		 Commands[i] = 'r';
	if (rout[j] == 'i')
		 Commands[i] = 'i';
	if (rout[j] == 'd')
		 Commands[i] = 'd';
	if (rout[j] == 'g')
		 Commands[i] = 'g';
	if (rout[j] == 'p' && rout[j + 5] != 'c')
		 Commands[i] = 't';
	if (rout[j] == 'p' && rout[j + 5] == 'c')
		 Commands[i] = 'c';
	if (rout[j] == 'b')
		 Commands[i] = 'b';
	if (rout[j] == '*')
		 return i;
	if (rout[j] == 'e')
		 Commands[i] = 'e';
	i++;
	return i;
	
}
