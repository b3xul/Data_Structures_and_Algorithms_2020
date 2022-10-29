#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

Item** malloc2dR(int nr, int nc){
    int i;
    Item** a=(Item**)malloc(sizeof(Item*));
    for(i=0;i<nr;i++)
        a[i]=(Item*)malloc(nc*sizeof(Item));

    return a;
}

void* malloc2dP(Item*** p, int nr, int nc){
    int i;
    Item** a=(Item**)malloc(sizeof(Item*));
    for(i=0;i<nr;i++)
        a[i]=(Item*)malloc(nc*sizeof(Item));

    (*p)=a;
}
