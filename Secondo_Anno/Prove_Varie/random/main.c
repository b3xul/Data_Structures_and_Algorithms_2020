#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
   time_t t;

   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 49 */

   printf("%d\n", rand() % 11);
   printf("%d\n", rand() % 13);
   printf("%d\n", rand() % 26);
   printf("%d\n", rand() % 7);
   printf("%d\n", rand() % 10);
   printf("%d\n", rand() % 19);
   printf("%d\n", rand() % 11);
   printf("%d\n", rand() % 4);
   printf("%d\n", rand() % 19);
   printf("%d\n", rand() % 3);
   printf("%d\n", rand() % 7);
   printf("%d\n", rand() % 3);


   return(0);
}
