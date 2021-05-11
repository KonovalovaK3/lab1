#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct string {
    //длина строки с учетом \0
    unsigned long long len;
    void* mass;
} STRING;

void constructorString(STRING* s, const char* str) {
    s->len = strlen(str) + 1;
    s->mass = (char*) malloc(sizeof(char) * s->len);
    strcpy(s->mass, str);
}

void constructorStringN(STRING* s, unsigned long long n) {
    s->len = n;
    s->mass = (char*) malloc(sizeof(char) * s->len);
}

void destructor(STRING* s) {
    free(s->mass);
    s->len = 0;
}

STRING* concat(STRING* s1, STRING* s2) {
    STRING* res = (STRING*) malloc(sizeof(STRING));
    constructorStringN(res, s1->len + s2->len - 1);
    strcpy(res->mass, s1->mass);
    strcat(res->mass, s2->mass);
    return res;
}

void print(STRING* s) {
    printf("%s", (char *)s->mass);
}

STRING* subString(const STRING* s, int i, int j) {
    if (i < 0 || j <= 0 || i >= j || j > s->len)
        return NULL;
    STRING* res = (STRING*) malloc(sizeof(STRING));
    constructorStringN(res, j - i);
    for (int k = i, g = 0; k < j; k++, g++) {
        ((char*)res->mass)[g] = ((char*)s->mass)[k];
    }
    ((char*)res->mass)[j - i] = '\0';
    return res;
}

int find(const STRING* s1, const STRING* s2, int sensitive) {
    for (int i = 0; i <= s1->len - s2->len; i++) {
        if (sensitive == 1 && ((char*)s1->mass)[i] == ((char*)s2->mass)[0] || sensitive == 0
        && tolower(((char*)s1->mass)[i]) == tolower(((char*)s2->mass)[0])) {
            int check = 0;
            for (int j = 0; j < s2->len - 1; j++) {
                if (sensitive == 1 && ((char*)s1->mass)[i + j] == ((char*)s2->mass)[j]
                || sensitive == 0 && tolower(((char*)s1->mass)[i + j]) == tolower(((char*)s2->mass)[j]))
                    check++;
            }
            if (check == s2->len -1){
                return i;
            }
        }
    }
    return -1;
}

int main() {
    printf("Input the string\n");
    char buf[512];
    int check = scanf("%s", buf);
    if (check <= 0) {
        printf("ERROR\n");
        return 1;
    }
    STRING A;
    constructorString(&A, buf);
    printf("What should I do with this string? Command: 1 - concatenation, 2 - find, 3 - substring\n");
    int whattodo;
    check = scanf("%d", &whattodo);
    if (check <= 0){
        printf("ERROR\n");
        return 1;
    }
    int i, k, l;
    int choice;
    switch(whattodo) {
        case 1:
             printf("Input the second string\n");
            char buf2[512];
            check = scanf("%s", buf2);
            if (check <= 0){
                printf("ERROR!\n");
                return 1;
            }
            STRING B;
            constructorString(&B, buf2);
            STRING* res = concat(&A, &B);
            printf("The result is");
            print(res);
            destructor(res);
            free(res);
            destructor(&A);
            destructor(&B);
            break;
        case 2:
            printf("Input the second string\n");
            char buf3[512];
            check = scanf("%s", buf3);
            if (check <=0){
                printf("ERROR\n");
                return 1;
            }
            STRING C;
            constructorString(&C, buf3);
            printf("Input how to find: \n 0 - not sensitive\n 1 - sensitive to register\n");
            check = scanf("%d", &choice);
            if (choice < 0 || choice > 1 || check <= 0){
                printf("ERROR\n");
                return 1;
            }
            i = find(&A, &C, choice);
            if (i == -1){
                printf("there is no such string\n");
            } else {
                printf("The result is %d\n", i);
            }
            destructor(&A);
            destructor(&C);
            break;
        case 3:
            printf("Input the first number of substring\n");
            check = scanf("%d", &k);
            if (check <= 0){
                printf("ERROR");
                return 1;
            }
            printf("Input the last number of substring\n");
            check = scanf("%d", &l);
            if (check <= 0){
                printf("ERROR\n");
                return 1;
            }
            STRING* D = subString(&A, k, l);
            if (D == NULL){
                printf("ERROR!\n");
                return 1;
            }
            printf("The result is \t");
            print(D);
            destructor(D);
            free(D);
            destructor(&A);
            break;
        default:
            printf("Wrong command. Break");
    }
    return 0;
}

