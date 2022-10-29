#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 31

typedef struct item{
    char nome[MAX_STR];
    char rete[MAX_STR];
}Item;

typedef char* Key;

Key Item_get_key(Item* x);
Item Item_load(char* nome, char* rete);
Item Item_read(FILE* fp);
int Item_cmp(Item a, Item b);
void Item_store(Item x);
Item Item_set_void();
int Item_check_void(Item x);
#endif // ITEM_H_INCLUDED
