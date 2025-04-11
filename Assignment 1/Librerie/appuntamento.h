#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#ifndef appuntamento_h
#define appuntamento_h

typedef struct utente utente;
typedef struct dipendente dipendente;

// Definizione file
#define FILE_STORICO_TEST "../VincenzoMarotta-N86003005/File/storico_test.txt"
#define FILE_ULTIMI_VALORI "../VincenzoMarotta-N86003005/File/ultimi_valori.txt"
#define FILE_PRENOTAZIONE_APPUNTAMENTI "../VincenzoMarotta-N86003005/File/prenotazione_appuntamenti.txt"
#define FILE_RICHIESTE_APPUNTAMENTI "../VincenzoMarotta-N86003005/File/richieste_appuntamenti.txt"

// Struttura appuntamento
typedef struct appuntamento{
    int id;
    char cf[17];
    int giorno;
    char orario[20];
    char descrizioneSintomi;
    char esitoTampone[20];
    struct appuntamento *next;
    struct appuntamento *prev;
} appuntamento;

// Prototipi funzione
appuntamento *creaListaAppuntamenti();
appuntamento azzeraAppuntamento(appuntamento a);
appuntamento *inserisciAppuntamentiInCoda(appuntamento *lista, appuntamento a);
appuntamento *inserisciRichiesteInCoda(appuntamento *lista, appuntamento a);
void richiediAppuntamento(char cf[], char sintomi);
appuntamento *creaListaRichieste();
void stampaRichiesteAppuntamento(appuntamento *lista);
appuntamento *creaAppuntamenti(appuntamento *listaAppuntamenti, appuntamento *listaRichieste);
void fissaAppuntamenti(appuntamento *listaRichieste);
void stampaAppuntamenti(appuntamento *listaAppuntamenti);
boolean appuntamentoPresente(char cf[]);
boolean richiestaPresente(char cf[]);
void visualizzaAppuntamentoUtente(char cf[]);
void aggiungiAppuntamento(char cf[], char sintomi);
void cancellaAppuntamento(char cf[]);
void concretizzaTamponi();
void aggiungiStorico(appuntamento *a);
appuntamento *creaStoricoAppuntamento();
appuntamento recuperaUltimiValori(appuntamento a);
boolean storicoPresente(char cf[]);

#endif
