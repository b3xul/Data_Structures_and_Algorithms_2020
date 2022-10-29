#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

typedef struct symbtab *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
int     STcount(ST st);
void  	STinsert(ST st,Item x);
int     STsearch(ST st, Key k);
void	STdisplayByIndex(ST st, int index) ;

#endif
