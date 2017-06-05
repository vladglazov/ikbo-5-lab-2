#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *lenta;
int size = 1;
int location = 0;

int movl(void){
    if (location == 0){
        int i;
        int* temp;
        size++;
        temp = (int*) realloc (lenta, sizeof(int) * size);
        if(temp != NULL){
            for (i = size - 1; i != 0; i--)
                temp[i]=temp[i-1];
            temp[0] = 0;
            lenta = temp;
        }
        else
            return 1;
    }
    else location--;
    return 0;
}

int movr(void){
    if (location == (size - 1)){
        int* temp;
        size++;
        location++;
        temp = (int*) realloc (lenta, sizeof(int) * size);
        if(temp != NULL){
            temp[size-1] = 0;
            lenta = temp;
        }
        else
            return 1;
    }
    else location++;
    return 0;
}

int inc (void) {
    if(lenta[location] < 255) {
        lenta[location]++;
    }
    else {
        lenta[location] = 0;
    }
    return 0;
}

int dec (void) {
    if(lenta[location] > 0) {
        lenta[location]--;
    }
    else {
        lenta[location] = 255;
    }
    return 0;
}

int tasks (char** a, int first, int last) {
    int i, temp = 0;
    for (i = first; i < last; i++){
        if (strcmp(a[i], "movl") == 0) {
            movl();
        }
        else {
            if (strcmp(a[i], "movr") == 0) {
                movr();
            }
            else {
                if (strcmp(a[i], "inc") == 0) {
                    inc();
                }
                else {
                    if (strcmp(a[i], "dec") == 0) {
                        dec();
                    }
                    else {
                        if (strcmp(a[i], "print") == 0) {
                            printf("\n%d", lenta[location]);
                        }
                        else {
                            if (strcmp(a[i], "get") == 0){
                                printf("\nEnter symbol:");
                                lenta[location] = getchar();
                            }
                            else {
                                if (strcmp(a[i], "printc") == 0) {
                                    printf("\n%c", lenta[location]);
                                }
                                else {
                                    if (strcmp(a[i], "begin") == 0) {
                                        temp = i + 1;
                                    }
                                    else {
                                        if (strcmp(a[i], "end") == 0) {
                                            while (lenta[location] != 0) {
                                                tasks(a, temp, i);
                                            }
                                        }
                                        else {
                                            printf("\nerror");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

char* delspace (char* s, char* a){
    int i, j;
    j = 0;
    a = (char*)malloc(sizeof(char) * 6);
    for (i = 0; s[i]; i++){
        if (s[i] != ' ' && s[i] != '\n'){
            a[j] = s[i];
            j++;
            a = (char*)realloc(a, (j + 6)*sizeof(char));
        }
    }
    a = (char*)realloc(a, j*sizeof(char));
    return a;
}

int main(int argc, char* argv[]){
    char s[255];
    char **a;
    int n = 0, i = 0;;
    char *filename = NULL;
    FILE* f;
    f = fopen("instruction.txt", "r");
    while (f == NULL) {
        printf("Enter a current filename: ");
        scanf("%s", filename);
        f = fopen(filename, "rb");
    }
    a = (char**)malloc((n + 1)*sizeof(char*));
    while (fgets(s, 255, f)){
        if (s[0] != '*') {
            a[n] = delspace(s, a[n]);
            n++;
            a = (char**)realloc(a, (n + 1)*sizeof(char*));
        }
    }
    fclose(f);
    lenta = (int*)malloc(sizeof(int));
    lenta[location]=0;
    tasks(a, 0, n);
    for(i = 0; i < n; i++) {
        free(a[n]);
    }
    free(a);
    printf("\n Tape: ");
    for(i = 0; i < size; i++) {
        printf("%d", lenta[i]);
    }
    return 0;
}