
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"
int main(int argc, char **argv) {

	FILE *fp;
	char buffer[255],com[255],name[255];
	long int b[10];
	DLLIST *curr;
	size_t i=-1;

	if (argc != 2) {
		printf("Please enter file name:\n");
		scanf("%s", name);
	}
	else
		strcpy(name, argv[1]);
	fp = fopen(name, "r");
	while (fp==NULL) {
		printf("Can't open file.Try again:\n");
		scanf("%s", name);
		fp = fopen(name, "r");
	}

	curr=DLCreate();

	while (fgets(buffer, 256, fp)) {

		delsp(buffer,com);

		if (!strcmp(com, "movl")) {
			if (curr->prev == NULL) {
				DLAddBefore(curr);
				curr = curr->prev;
			}
			else
				curr = curr->prev;
			continue;
		}

		if (!strcmp(com, "movr")) {
			if (curr->next == NULL) {
				DLAddAfter(curr);
				curr = curr->next;
			}
			else
				curr = curr->next;
			continue;
		}

		if (!strcmp(com, "inc")) {
			if (curr->data > 255) {
				printf("Too big value. Can't increase.\n");
				curr->data = 0;
				continue;
			}
			curr->data++;
			continue;
		}

		if (!strcmp(com, "dec")) {
			if (curr->data == 0) {
				printf("Too small value. Can't decrease.\n");
				continue;
			}
			curr->data--;
			continue;
		}

		if (!strcmp(com, "print")) {
			printf("Your data: %d\n", curr->data);
			continue;
		}

		if (!strcmp(com, "get")) {
			printf("Enter data: ");
			scanf("%d", &curr->data);
			continue;
		}

		if (!strcmp(com, "printc")) {
			printf("Your symbol: %c\n", curr->data);
			continue;
		}


		if (!strcmp(com, "begin")) {
            if (curr->data==0){
                while(1){
                    if (fgets(buffer, 256, fp)==0)
                        return 0;
                    delsp(buffer,com);
                    if (!strcmp(com,"end"))
                        break;
                }
            }
			i++;
			b[i] = ftell(fp);
			if (i > 9) {
				printf("Eror.Too much nesting\n");
				break;
			}
			continue;
		}

		if (!strcmp(com, "end")) {

			if (i == -1) {
				printf("Eror.Miss begin");
				break;
			}

			if (curr->data != 0) {
				fseek(fp, b[i], SEEK_SET);
				continue;
			}
			i--;
			continue;
		}

		if (!strcmp(com, "skip")) {
			continue;
		}

		printf("Invalid sintax\n");
		break;
	}
	DestroyDL(curr);
	return 0;
}

