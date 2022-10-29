#ifndef BST_H_DEFINED
#define BST_H_DEFINED

#include "Item.h"

typedef struct node* link;
typedef struct _bst *Bst;

int BSTcount(Bst bst);
void BSTdelete(Bst bst, Key k);
int BSTempty(Bst bst);
Bst BSTinit();
void BSTinsertLeafI(Bst bst, ITEM x);
void BSTinsertLeafR(Bst bst, ITEM x);
void BSTinsertRoot(Bst bst, ITEM x);
ITEM BSTmax(Bst bst);
ITEM BSTmin(Bst bst);
ITEM BSTpred(Bst bst, Key k);
ITEM BSTsearch(Bst bst, Key k);
ITEM BSTselect(Bst bst, int k);
void BSTsortInOrder(Bst bst);
void BSTsortPostOrder(Bst bst);
void BSTsortPreOrder(Bst bst);
ITEM BSTsucc(Bst bst, Key k);

#endif // BST_H_DEFINED