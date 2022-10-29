#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item ITEMscan() {
  Item val=(char*)malloc(MAXS*sizeof(char));
  printf("name: ");
  scanf("%s", val);
  return val;
}

Item ITEMnew(char* x){
    Item val;
    val=strdup(x);
    return val;
}

void ITEMfree(Item val){
    free(val);
}

void ITEMstore(Item val) {
  printf("name: %s\n", val);
}

int ITEMcheckNull(Item val) {
  if (strcmp(val,"")==0)
    return 1;
  return 0;
}

Item ITEMsetNull() {
  Item val = {""};
  return val;
}

Key KEYget(Item *pval) {
  return *pval;
}

int KEYcmp(Key k1, Key k2) {
  return strcmp(k1, k2);
}

