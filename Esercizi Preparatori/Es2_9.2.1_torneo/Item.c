#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

struct item {
  char* name;
  int points;
};

Item ITEMscan(FILE* in) {
  char buf[MAXS];
  Item val;
  val=(Item)calloc(1,sizeof(struct item));

  fscanf(in,"%s", buf);
  val->name=strdup(buf);
  val->points=10;

  return val;
}

void ITEMstore(Item val) {
  printf("name: %s points: %d\n", val->name, val->points);
}

void ITEMstoreFile(Item val, FILE* out) {
  fprintf(out,"name: %s points: %d\n", val->name, val->points);
}

Item ITEMsetNull() {
  Item val;

  val=(Item)calloc(1,sizeof(struct item));

  val->points=-1;
  return val;
}

int ITEMcheckNull(Item val) {
  if (val->points==-1)
    return 1;
  return 0;
}

void ITEMfree(Item val){
    if(ITEMcheckNull(val))
        return;
    free(val->name);
    free(val);
}

char* NAMEget(Item val){
    return val->name;
}

int  KEYcmp(Key k1, Key k2) {
  if (k1 < k2)
    return -1;
  else if ( k1 == k2)
    return 0;
  return 1;
}

Key KEYget(Item val) {
  return val->points;
}

int exchange_points(Item winner, Item loser){
    int points=(int) ceil((loser->points)*0.25);

    loser->points-=points;
    winner->points+=points;

    return points;
}
