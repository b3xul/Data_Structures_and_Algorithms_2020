#include "item.h"

Key key(Item item) {
  return item;
}

Item ITEMscan() {
  Item item;
  scanf("%d", &item);
  return item;
}

void ITEMshow(Item item) {
  printf("%d \n", item);
}

Item ITEMrand() {
  Item item = maxKey*rand()/RAND_MAX;
  return item;
}

int ITEMlt(Item x, Item y){
    return (key(x)<key(y));
}

int ITEMgt(Item x, Item y){
    return (key(x)>key(y));
}
