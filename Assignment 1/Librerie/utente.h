#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#ifndef utente_h
#define utente_h

// Definizione file
#define FILE_UTENTI_LOGIN "../VincenzoMarotta-N86003005/File/utenti_login.txt"

typedef struct appuntamento appuntamento;
typedef struct dipendente dipendente;

// Struttura utente
typedef struct utente{
    char cf[17];
    char password[30];
    char nome[30];
    char cognome[30];
    char dataNascita[11];
    char telefono[11];
    struct utente *next;
} utente;
 
// Prototipi funzione
utente *creaListaUtenti();
utente *inserisciUtenteInCoda(utente *lista, utente u);
utente azzeraUtente(utente u);
void stampaListaUtenti(utente *lista);
utente inizializzaUtente();
void aggiungiUtente();
void checkLoginUtente();
void recuperaEsitoUtente(char cf[]);
boolean isAllDigit(char stringa[], int len);
boolean isAllAlpha(char stringa[], int len);
boolean checkCorrettezzaData(char dataNascita[]);

#endif
