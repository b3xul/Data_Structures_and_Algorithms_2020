#include <stdio.h>
#include <stdlib.h>
#define PREZZO 100
#define DOTI 40
#define MESI 20

int main()
{
    int price, features, months, years;
    printf("Quante features deve avere? Da quanti anni e' sulla piazza? ");
    scanf("%d%d", &features,&years);

    months=years*12;
    price=PREZZO+DOTI*features-MESI*months;

    if(price<0) {
        printf("No dai e' un catorcio, rinunciaci");
    }
    else {
        printf("Ti costera' %d euro", price);
    }
    return 0;
}
