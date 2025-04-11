#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#ifndef piattaforma_h
#define piattaforma_h

// Definizione file
#define FILE_ELENCO_POSITIVI "../VincenzoMarotta-N86003005/File/elenco_positivi.txt"

typedef struct appuntamento appuntamento;
typedef struct utente utente;
typedef struct dipendente dipendente;

// Prototipi funzione
appuntamento *creaListaPositivi();
appuntamento *inserisciPositivoInCoda(appuntamento *lista, appuntamento u);
boolean positivoPresente(char cf[]);
void aggiungiPositivo(char cf[], char sintomi);
void cancellaPositivo(char cf[]);
void stampaPositivi(appuntamento *elencoPositivi);


#endif
