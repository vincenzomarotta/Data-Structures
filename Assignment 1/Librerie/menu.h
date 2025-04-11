#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#ifndef menu_h
#define menu_h

typedef struct appuntamento appuntamento;
typedef struct utente utente;
typedef struct dipendente dipendente;

// Prototipi funzione
void menuPrincipale();
void registrazione();
void login();
void infoCovid();
void menuUtente(char cf[]);
void menuDipendente(char codiceDipendente[]);
void piattaforma();


#endif
