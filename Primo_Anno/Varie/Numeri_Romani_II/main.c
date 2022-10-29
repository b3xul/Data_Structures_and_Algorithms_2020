#include <stdio.h>
#include <stdlib.h>
#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

int main()
{
    int x;
    char y;

    printf("Inserisci char: ");
    scanf("%c", &y);

    x=sizeof(y);
    printf("%d",x);

    return 0;
}
