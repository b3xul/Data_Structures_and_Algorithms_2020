#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Item.h"

Item ITEMscan(FILE *fin) {
  Item item;
  if(fscanf(fin,"%s %f", item.name, &item.price)!=2)
    item=ITEMsetNull();
  return item;
}

void ITEMstore(FILE *out, Item x) {
  fprintf(out, "%s : %f\n", x.name, x.price);
}

Item ITEMsetNull() {
  Item x = {-1, ""};
  return x;
}

int ITEMcheckNull(Item x) {
  if(x.price==-1)
    return 1;
  return 0;
}

int ITEMgreater(Item A, Item B) {
  return (KEYget(A) > KEYget(B));
}

Key KEYcmp(Key A, Key B){
    if(A<B)
        return -1;
    else if(A==B)
        return 0;
    else
        return 1;
}

Key KEYget(Item val){
  return val.price;
}

SearchKey  SearchKEYget(Item* val){
    return val->name;
}
int SearchKEYcmp(SearchKey A, SearchKey B){
    return strcmp(A,B);
}
