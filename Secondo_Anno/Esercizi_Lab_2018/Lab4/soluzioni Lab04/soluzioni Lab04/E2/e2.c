#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define N 30
#define REQUIRE_INPUT 0

int count(int *a, int n, int val);
void majorityNlogNRec( int *a, int n);
int majorityR( int *a, int n, int l, int r);

int main(int argc, char **argv) {
  int i, n = 10, a[N] = {1,0,1,1,0,1,9,4,1,1};

#if REQUIRE_INPUT
  do {
 		printf("Input number of elements: ");
 		scanf("%d", &n);
  } while (n <= 0 || n > N);
  for(i=0;i<n;i++)
    scanf("%d", &a[i]);
#endif /* REQUIRE_INPUT */

  printf("NlogN recursive algorithm\n");
  majorityNlogNRec(a, n);

  return 0;
}

int count(int *a, int n, int val){
  int i, cnt=0;
  for (i=0; i<n; i++)
    if (a[i]==val)
      cnt++;
  return cnt;
}

void majorityNlogNRec( int *a, int n) {
  int l=0, r=n-1, res;
  res = majorityR(a, n, l, r);
  if (res==-1)
    printf("No majority element\n");
  else
    printf("Majority element = %d\n", res);
}

int majorityR( int *a, int n, int l, int r) {           //Lavora su ogni sottovettore percorrendo l'albero del mergesort
  int resLeft, resRight, resLeftCnt, resRightCnt;
  int m = (l + r)/2 ;
  if (l == r)           //valore nel vettore di 1 sola casella
    return a[l] ;

  resLeft = majorityR(a, n, l, m);          //Elemento maggioritario a sx
  resRight = majorityR(a, n, m+1, r);       //Elemento maggioritario a dx

  if (resLeft==resRight) //Elemento maggioritario tra sottovettore sx e dx
    return resLeft;

  resLeftCnt = count(a, n, resLeft);    //Numero di elementi uguali a quello maggioritario a sx nel vettore
  resRightCnt = count(a, n, resRight);  //Numero di elementi uguali a quello maggioritario a dx nel vettore

  if (resLeftCnt > n/2)
    return resLeft;
  if (resRightCnt > n/2)
    return resRight;
  return -1;
}
