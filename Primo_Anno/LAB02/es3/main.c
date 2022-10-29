#include <stdio.h>
#include <stdlib.h>

int main()
{
    float length, width, perimeter;
    printf("Inserisci base e altezza: ");
    scanf("%f%f", &length,&width);

    perimeter=length*width;

    printf("Il perimetro vale %f", perimeter);
    return 0;
}
