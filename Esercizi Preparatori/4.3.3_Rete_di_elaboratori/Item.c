#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item ITEMnew(char* name, int index){
    Item val;
    strcpy(val.name,name);
    return val;
}

Item ITEMscan() {
  Item val;
  printf("name: ");
  scanf("%s", val.name );
  return val;
}

void ITEMstore(Item val) {
  printf("name: %s ", val.name);
}

int ITEMcheckNull(Item val) {
  if (strcmp(val.name,"")==0)
    return 1;
  return 0;
}

Item ITEMsetNull() {
  Item val = {""};
  return val;
}

Key KEYget(Item *pval) {
  return pval->name;
}

int KEYcmp(Key k1, Key k2) {
  return strcmp(k1, k2);
}

