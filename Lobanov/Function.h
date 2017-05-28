typedef struct DLLIST {
	struct DLLIST *next;
	struct DLLIST *prev;
	int data;
} DLLIST;

DLLIST* DLCreate() {
	DLLIST *NewItem;
	NewItem = (DLLIST*)malloc(sizeof(DLLIST));
	if (NewItem != NULL) {
		NewItem->prev = NewItem->next = NULL;
		NewItem->data = 0;
	}
	else {
		printf("Eror.No memory\n");
		return(NULL);
	}
	return(NewItem);
}
void DLAddBefore(DLLIST *ExitingItem) {
	DLLIST *NewItem;
	NewItem=DLCreate();
	if (ExitingItem != NULL && NewItem != NULL) {
		NewItem->next = ExitingItem;
		NewItem->prev = ExitingItem->prev;
		ExitingItem->prev = NewItem;
	}
	if (NewItem->prev != NULL) {
		NewItem->prev->next = NewItem;
	}
	return;
}
void DLAddAfter(DLLIST *ExitingItem) {
	DLLIST *NewItem;
	NewItem = DLCreate();
	if (ExitingItem != NULL && NewItem != NULL) {
		NewItem->next = ExitingItem->next;
		NewItem->prev = ExitingItem;
		ExitingItem->next = NewItem;
	}
	if (NewItem->next != NULL) {
		NewItem->next->prev = NewItem;
	}
	return;
}
void GetFirst(DLLIST *current){
	while (current->prev != NULL)
		current = current->prev;
	return;
}
void DestroyDL(DLLIST *current) {
	DLLIST *Next;
	GetFirst(current);
	while (current->next != NULL) {
		Next = current->next;
        free(current);
        current = Next;
	}
	free(current);
	return;
}
void delsp(char* buffer, char *com) {
	int i, j = 0;
	char command[255];
	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t') {
			command[j] = buffer[i];
			if (command[0] == '*') {
				strcpy(com, "skip");
			}
			j++;
		}
	command[j] = '\0';
	strcpy(com,command);
}
