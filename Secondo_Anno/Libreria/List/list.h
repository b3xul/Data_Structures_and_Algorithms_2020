#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "Item.h"

typedef struct node* link;
typedef struct node{
    Item val;
    link next;
}Node;


link new_node(Item val, link next);
link list_insert_head(link x, Item item);
void list_insert_head_P(link *hp, Item val);
link list_insert_tail(link x, Item item);
void list_insert_tail_P(link *hp, Item val);
void list_insert_tail_Fast(link *hp,link *tp,Item val);
Item list_search(link x, Key k);
link list_delete_head(link x);
Item list_extract_headP(link *x);
link list_delete_key(link x, Key k);
link list_delete_keyR(link x, Key k);
Item list_extract_keyP(link *x, Key k);
link sorted_list_insert(link x, Item item);
Item sorted_list_search(link x, Key k);
link sorted_list_delete(link x, Key k);
link listReverse(link x);
link listSort(link h);
link listSortF(link h);
void list_show(link x);
void list_free(link x);

#endif // LIST_H_INCLUDED
