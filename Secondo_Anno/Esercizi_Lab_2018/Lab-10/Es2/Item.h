#include <stdio.h>
#include <stdlib.h>
#define MAX_STR 101

typedef struct esercizio{
    char nome[MAX_STR]; int tipo; int d_ingresso; int d_uscita; int requisito_precedenza; int finale; float valore; int difficolta;
} Item;

int  ITEMeq(Item A, Item B);
int  ITEMneq(Item A, Item B);
int  ITEMlt(Item A, Item B);
int  ITEMgt(Item A, Item B);
Item ITEMscan(FILE* fp);
void ITEMshow(Item A);

