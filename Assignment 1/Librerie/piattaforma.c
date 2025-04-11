#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "piattaforma.h"
#include "menu.h"
#include "utente.h"
#include "appuntamento.h"
#include "laboratorio.h"


/* Funzione che crea una lista di positivi da file
Parametri:
Ritorna: Lista di "appuntamenti" composti da cf e sintomi
*/
appuntamento *creaListaPositivi(){
    appuntamento *listaPositivi = NULL;
    // Apro il file in lettura
    FILE *elenco;
    elenco = fopen(FILE_ELENCO_POSITIVI,"r");

    // Controllo che il file si sia aperto correttamente
    if(elenco == NULL){
        printf("Problema di apertura del file nei nostri sistemi, riprova piu' tardi.\n");
        system("PAUSE");
        return listaPositivi;
    }

    char riga[25];
    appuntamento u;

    // Leggo i CF e i relativi sintomi
    while(fgets(riga, 25,elenco) != NULL){
        int i=0, tmp = 0, index = 0;
        u = azzeraAppuntamento(u);

        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            u.cf[index] = riga[tmp];
            index++;
        }
        i++;

        u.descrizioneSintomi = riga[i];

        listaPositivi = inserisciPositivoInCoda(listaPositivi, u);
    }
    fclose(elenco);
    return listaPositivi;
}

/* Funzione che inserisce in lista i positivi
Parametri: Lista e utente con cf e sintomi
Ritorna: Lista di "appuntamenti" composti da cf e sintomi
*/
appuntamento *inserisciPositivoInCoda(appuntamento *lista, appuntamento u){
    if(lista == NULL){
        appuntamento *lista = (appuntamento *)malloc(sizeof(appuntamento));
        lista->next = NULL;
        lista->descrizioneSintomi = u.descrizioneSintomi;
        strcpy(lista->cf, u.cf);
        return lista;
    }
    else{
        lista->next = inserisciPositivoInCoda(lista->next, u);
    }
    return lista;
}

/* Funzione che controlla la presenza di un cf tra i positivi
Parametri: Codice fiscale utente
Ritorna: boolean
*/
boolean positivoPresente(char cf[]){
    appuntamento *listaPositivi = creaListaPositivi();
    if(listaPositivi == NULL){
        return false;
    }
    else{
        while(listaPositivi != NULL){
            if(!strcmp(listaPositivi->cf,cf)){
                return true;
            }
            listaPositivi = listaPositivi->next;
        }
        return false;
    }
}

/* Funzione che aggiunge un positivo all'elenco
Parametri: Codice Fiscale e Sintomi
Ritorna:
*/
void aggiungiPositivo(char cf[], char sintomi){

    char codiceFiscale[17];
    strcpy(codiceFiscale,cf);
    // Se il positivo è presente non lo aggiungo
    if(positivoPresente(codiceFiscale)){
        return;
    }

    FILE *elenco;
    elenco = fopen(FILE_ELENCO_POSITIVI, "a");

    if(elenco == NULL){
        printf("Errore di apertura del file nei nostri sistemi, riprova piu' tardi.\n");
        return;
    }

    fprintf(elenco,"%s %c \n", codiceFiscale, sintomi);
    fclose(elenco);
    return;
}

/* Funzione che cancella un positivo all'elenco
Parametri: Codice Fiscale
Ritorna:
*/
void cancellaPositivo(char cf[]){

    char codiceFiscale[17];
    strcpy(codiceFiscale,cf);

    if(!positivoPresente(codiceFiscale)){
        return;
    }

    appuntamento *listaPositivi = creaListaPositivi();

    appuntamento *successivo = listaPositivi;
    appuntamento *precendente = NULL;

    if(!strcmp(successivo->cf,codiceFiscale)){
        listaPositivi = successivo->next;
        free(successivo);
    }
    else{
        while(successivo->next != NULL){
            if(!strcmp(successivo->next->cf,codiceFiscale)){
                precendente = successivo->next;
                successivo->next = successivo->next->next;
                free(precendente);
            }
            else{
                successivo = successivo->next;
            }
        }
    }


    FILE *elenco;
    elenco = fopen(FILE_ELENCO_POSITIVI, "w");

    if(elenco == NULL){
        printf("Errore di apertura del file nei nostri sistemi, riprova piu' tardi.\n");
        return;
    }

    while(listaPositivi != NULL){
        fprintf(elenco,"%s %c \n", listaPositivi->cf, listaPositivi->descrizioneSintomi);
        listaPositivi = listaPositivi->next;
    }

    fclose(elenco);
    return;
}

/* Funzione che stampa la lista di positivi
Parametri: lista dei positivi
Ritorna:
*/
void stampaPositivi(appuntamento *elencoPositivi){
    system("cls");
    printf("\t\t\t---- ELENCO POSITIVI ----\n\n");

    while(elencoPositivi != NULL){
        printf("Codice Fiscale: %s\n",elencoPositivi->cf);
        printf("Tipologia Sintomi: %c", elencoPositivi->descrizioneSintomi);
        printf("\n=================================\n");
        elencoPositivi = elencoPositivi->next;
    }
    return;
}
