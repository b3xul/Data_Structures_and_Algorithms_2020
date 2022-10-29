#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

#include "Item.h"

typedef struct symbtab *ST;

ST  	STinit(int maxN) ;
void    STfree(ST st) ;
int		STcount(ST st) ;
int  	STinsert(ST st,Item val) ;
Item    STsearch(ST st, Key k) ;
Item    STsearchByIndex(ST st, int i);
int     STgetIndex(ST st, Key k) ;
void	STdelete(ST st, Key k) ;
void	STdisplay(ST st) ;

#endif
