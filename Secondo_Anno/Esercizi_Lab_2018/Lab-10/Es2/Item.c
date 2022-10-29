#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan(FILE* fp){
    Item e;
    fscanf(fp,"%s%d%d%d%d%d%f%d",e.nome,&e.tipo,&e.d_ingresso,&e.d_uscita,&e.requisito_precedenza,&e.finale,&e.valore,&e.difficolta);
    return e;
}

void ITEMshow(Item item) {
  printf("%s : %f \n", item.nome, item.valore);
}

int ITEMeq(Item A, Item B) {
  return (float)(A.valore/A.difficolta) == (float)(B.valore/B.difficolta);
}

int ITEMneq(Item A, Item B) {
  return (A.valore/A.difficolta) != (B.valore/B.difficolta);
}

int ITEMlt(Item A, Item B) {
  return ((A.valore/A.difficolta) < (B.valore/B.difficolta));
}

int ITEMgt(Item A, Item B) {
  return ((B.valore/B.difficolta) > (B.valore/B.difficolta));
}

