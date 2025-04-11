#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#ifndef laboratorio_h
#define laboratorio_h

// Definizione file
#define FILE_DIPENDENTI_LOGIN "../VincenzoMarotta-N86003005/File/dipendenti_login.txt"

typedef struct appuntamento appuntamento;
typedef struct utente utente;

// Struttura dipendente
typedef struct dipendente{
    char codiceDipendente[11];
    char password[30];
    char nome[30];
    char cognome[30];
    char dataNascita[11];
    char telefono[11];
    struct dipendente *next;
} dipendente;

// Prototipi funzione
dipendente *creaListaDipendenti();
dipendente *inserisciDipendenteInCoda(dipendente *lista, dipendente d);
dipendente azzeraDipendente(dipendente d);
void stampaListaDipendenti(dipendente *lista);
dipendente inizializzaDipendente();
void aggiungiDipendente();
void checkLoginDipendente();



#endif
