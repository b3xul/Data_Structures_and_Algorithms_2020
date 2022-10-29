typedef enum comando_e{
    date_c, partenza_c, capolinea_c, ritardo_c, ritardo_tot_c, fine_c, errore_c
} sceltaMenu;

struct{ sceltaMenu codice;
        char* prompt;
        char* comando;      }scelte[]=  {
                                        {date_c,"Elencare tutte le corse partite in un certo intervallo di date",  "date"},
                                        {partenza_c,"Elencare tutti le corse partite da una certa fermata",  "partenza"},
                                        {capolinea_c,"Elencare tutti le corse che fanno capolinea in una certa fermata",   "capolinea"},
                                        {ritardo_c,"Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date","ritardo"},
                                        {ritardo_tot_c,"Elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta","ritardo_tot"},
                                        {fine_c,"Terminare il programma","fine"},
                                        {errore_c,NULL,NULL}
                                        };
