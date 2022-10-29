#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct node* link;
typedef struct node{
    int val;
    link next;
}Node;

link new_node(int val, link next);
link list_insert_head(link x, int item);
void list_show(link x);
void list_free(link x);

#endif // LIST_H_INCLUDED
