#include "ST.h"

struct SymbolTable{Item* v; int n; int n_alloc; };

static int binary_search(Item* v, Item x, int l, int r);

ST ST_init(int maxN){
    int i;
    ST st=(ST)calloc(1,sizeof(struct SymbolTable));
    st->v=(Item*)malloc(maxN*sizeof(Item));
    for(i=0;i<maxN;i++){
        st->v[i]=Item_set_void();
    }
    st->n=0;
    st->n_alloc=maxN;
    return st;
}

void ST_insert(ST st, Item x){
    int i;

    if(st->n_alloc==st->n){
        st->n_alloc*=2;
        st->v=(Item*)realloc(st->v,st->n_alloc*sizeof(Item));
        if(st->v==NULL){
            fprintf(stderr,"Errore allocazione!\n");
            exit(-1);
        }
    }

    //st->n rappresenta la prima casella libera ma già allocata del vettore, per cui posso copiarvi st->v[i-1] senza temere di perdere dati
    for(i=st->n; i>0 && Item_cmp( x,st->v[i-1] )<0 ;i--)
        st->v[i]=st->v[i-1];

    st->v[i]=x;
    st->n++;
}

int ST_search(ST st, Item x){
    return binary_search(st->v, x, 0, st->n-1);
}

static int binary_search(Item* v, Item x, int l, int r){
    int m,pos;

    while(l<=r){
        m=(l+r)/2;
        pos=Item_cmp( x,v[m] );
        if(pos==0){
            return m;
        }
        else if(pos<0)
            r=m-1;
        else
            l=m+1;
    }
    return -1;
}

Item ST_search_by_index(ST st, int index){
    if(index>=0 && index<st->n)
        return st->v[index];
    return Item_set_void();
}

int ST_count(ST st){
    return st->n;
}

void ST_store(ST st, Item x){
    Item_store(st->v[ST_search(st,x)]);
}

void ST_store_by_index(ST st, int index){
    Item_store(st->v[index]);
}

void ST_free(ST st){
    free(st->v);
    free(st);
}
