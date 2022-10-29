#include "Item.h"

Item ITEMscan() {
  Item item;
  printf("x = ");
  scanf("%d", &item.F);
  printf("y = ");
  scanf("%d", &item.S);
  return item;
}

void ITEMshow(Item item) {
  printf("a.F= %6d \t a.S= %6d \n", item.F, item.S);
}

int ITEMeq(Item A, Item B) {
  return (A.F == B.F);
}

int ITEMneq(Item A, Item B) {
  return (A.F != B.F);
}

int ITEMlt(Item A, Item B) {
  return (A.F < B.F);
}

int ITEMgt(Item A, Item B) {
  return (A.F > B.F);
}

