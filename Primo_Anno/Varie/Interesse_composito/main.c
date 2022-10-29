#include <stdio.h>
#include <stdlib.h>

int main()
{
    int risparmio_annuo=10000;
    int interesse=5;
    int anno;

    int risultato=0;

    for(anno=0;anno<2;anno++){
        risultato+=risparmio_annuo;
        risultato+=risultato*interesse/100;
    }

    printf("Mettendo da parte %d euro l'anno con un interesse del %d percento, in %d anni si ottengono %d soldi.",risparmio_annuo,interesse,anno,risultato);
    return 0;
}
