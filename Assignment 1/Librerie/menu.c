#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "menu.h"
#include "utente.h"
#include "appuntamento.h"
#include "piattaforma.h"
#include "laboratorio.h"


/* Funzione che stampa le scelte della schermata principale
Parametri:
Ritorna:
*/
void menuPrincipale(){
    system("cls");
    printf("\t\t\t---- SISTEMA GESTIONE TAMPONI MOLECOLARI ----\n\n");
    printf("Benvenuto nel sistema per la gestione dei tamponi molecolari per il COVID-19.\n");
    printf("Scegli che cosa vuoi fare:\n");
    printf("1. Registrazione\n");
    printf("2. Login\n");
    printf("3. Piattaforma - vedi la lista delle persone positive\n");
    printf("4. Informazioni sul COVID-19\n");
    printf("5. Chiudi il programma\n");
}

/* Funzione che si preoccupa della registrazione di utenti e dipendenti
Parametri:
Ritorna:
*/
void registrazione(){
    int scelta;
    do{
        system("cls");
        printf("\t\t\t---- REGISTRAZIONE ----\n\n");
        printf("Cosa vuoi fare?\n");
        printf("1. Registrazione utente\n");
        printf("2. Registrazione dipendente\n");
        printf("3. Menu' principale\n");

        printf("Inserire numero operazione: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                aggiungiUtente();
                printf("\nRegistrazione avvenuta con successo.\n");
                system("PAUSE");
                return;
            case 2:
                aggiungiDipendente();
                printf("\nRegistrazione avvenuta con successo.\n");
                system("PAUSE");
                return;
            case 3:
                return;
            default:
                printf("Operazione non valida, riprova.\n");
                system("PAUSE");
                break;
        }
    }while(1);
}

/* Funzione che si preoccupa del login di dipendenti e utenti
Parametri:
Ritorna:
*/
void login(){
    int scelta;
    do{
        system("cls");
        printf("\t\t\t---- LOGIN ----\n\n");
        printf("Cosa vuoi fare?\n");
        printf("1. Login utente\n");
        printf("2. Login dipendente\n");
        printf("3. Menu' principale\n");

        printf("Inserire numero operazione: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
               checkLoginUtente();
               return;
            case 2:
                checkLoginDipendente();
                return;
            case 3:
                return;
            default:
                printf("Operazione non valida, riprova.\n");
                system("PAUSE");
                break;
        }
    }while(1);
}

/* Funzione per stampare a video informazioni sul COVID-19
Parametri:
Ritorna:
*/
void infoCovid(){
    system("cls");
    printf("\t\t\t---- INFO COVID ----\n\n");
    printf("La sindrome respiratoria acuta grave Coronavirus-2 (SARS-CoV-2) e' il nome dato al nuovo coronavirus del 2019.\n");
    printf("COVID-19 e' il nome dato alla malattia associata al virus.\n");
    printf("La malattia da coronavirus colpisce in vari modi:\n");
    printf("\n[A]: Sintomi comuni - febbre, tosse, spossatezza\n");
    printf("\n[B]: Sintomi meno comuni - dolori muscolari, mal di gola, diarrea, congiuntivite, mal di testa, perdita di gusto e/o olfatto, eruzione cutanea\n");
    printf("\n[C]: Sintomi gravi - difficolta' respiratoria, dolore al petto, perdita di facolta' di parola e/o movimento\n");
    printf("\nSe presenti uno o piu' di questi sintomi resta a casa, non mettere a rischio la tua salute e quella di altre persone.\n");
    printf("\nRegistrati alla piattaforma o chiama un dottore del nostro laboratorio per prenotare un tampone molecolare.\n\n");
    system("PAUSE");
 }

/* Funzione che apre il menù delle opzioni utente
Parametri: Codice Fiscale utente
Ritorna:
*/
void menuUtente(char cf[]){
    int scelta;
    char codiceFiscale[17];
    char sintomi;
    strcpy(codiceFiscale,cf);
    while(1){
        system("cls");
        printf("\t\t\t---- BENVENUTO %s ----\n\n", codiceFiscale);
        printf("Scegli cosa vuoi fare: \n");
        printf("1. Richiedi un appuntamento\n");
        printf("2. Vedere appuntamento fissato\n");
        printf("3. Cancella Appuntamento\n");
        printf("4. Visualizzare Esito Tampone\n");
        printf("5. Chiudi programma\n");
        printf("Inserisci numero opzione: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                printf("\t\t\t---- RICHIESTA APPUNTAMENTO ----\n\n");
                printf("\nChe tipo di sintomi presenti?\n");
                printf("\n[A]: Sintomi comuni - febbre, tosse, spossatezza\n");
                printf("\n[B]: Sintomi meno comuni - dolori muscolari, mal di gola, diarrea, congiuntivite, mal di testa, perdita di gusto e/o olfatto, eruzione cutanea\n");
                printf("\n[C]: Sintomi gravi - difficolta' respiratoria, dolore al petto, perdita di facolta' di parola e/o movimento\n");
                printf("\n[D]: Nessun sintomo\n");
                printf("\nInserire tipologia sintomi: ");
                scanf(" %c", &sintomi);
                richiediAppuntamento(codiceFiscale, sintomi);
                printf("\nRichiesta effettuata correttamente.\n\n");
                system("PAUSE");
                break;
            case 2:
                visualizzaAppuntamentoUtente(codiceFiscale);
                break;
            case 3:
                printf("Cancellazione dell'appuntamento in corso.\n");
                cancellaAppuntamento(codiceFiscale);
                system("PAUSE");
                break;
            case 4:
                recuperaEsitoUtente(codiceFiscale);
                break;
            case 5:
                printf("\nGrazie per aver usato il sistema, a presto!\n");
                system("PAUSE");
                exit(1);
            default:
                printf("Operazione non valida, riprovare\n");
                system("PAUSE");
                break;
        }
    }
}

/* Funzione che apre il menù delle opzioni dipendente
Parametro: Array di char
Ritorna:
*/
void menuDipendente(char codiceDipendente[]){
    int scelta;
    char codDipendente[11];
    char sintomi;
    strcpy(codDipendente,codiceDipendente);
    appuntamento *a;
    char cf[17];
    while(1){
        system("cls");
        printf("\t\t\t---- BENVENUTO %s ----\n\n", codDipendente);
        printf("Scegli cosa vuoi fare: \n");
        printf("1. Visualizza storico test effettuati\n");
        printf("2. Visualizza e fissa appuntamenti richiesti\n");
        printf("3. Visualizza appuntamenti fissati\n");
        printf("4. Aggiungi Appuntamento\n");
        printf("5. Cancella Appuntamento\n");
        printf("6. Chiudi programma\n");
        printf("Inserisci numero opzione: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                a = creaStoricoAppuntamento();
                printf("\t\t\t---- STORICO APPUNTAMENTI ----\n\n");
                stampaAppuntamenti(a);
                free(a);
                break;
            case 2:
                a = creaListaRichieste();
                if(a == NULL){
                    printf("\nNon ci sono richieste.\n\n");
                    system("PAUSE");
                    free(a);
                    break;
                }
                printf("\nRICHIESTE DI APPUNTAMENTO:\n\n");
                stampaRichiesteAppuntamento(a);
                printf("\nFisso gli appuntamenti dando precedenza ai sintomatici...\n");
                fissaAppuntamenti(a);
                printf("Appuntamenti fissati!\n\n");
                system("PAUSE");
                free(a);
                break;
            case 3:
                a = creaListaAppuntamenti();
                printf("\t\t\t---- APPUNTAMENTI FISSATI ----\n\n");
                stampaAppuntamenti(a);
                free(a);
                break;
            case 4:
                printf("\nInserisci Codice Fiscale: ");
                scanf("%s", cf);
                printf("\nChe tipo di sintomi presenti?\n");
                printf("\n[A]: Sintomi comuni - febbre, tosse, spossatezza\n");
                printf("\n[B]: Sintomi meno comuni - dolori muscolari, mal di gola, diarrea, congiuntivite, mal di testa, perdita di gusto e/o olfatto, eruzione cutanea\n");
                printf("\n[C]: Sintomi gravi - difficolta' respiratoria, dolore al petto, perdita di facolta' di parola e/o movimento\n");
                printf("\n[D]: Nessun sintomo\n");
                printf("Inserire tipologia sintomi: ");
                scanf(" %c", &sintomi);
                aggiungiAppuntamento(cf, sintomi);
                break;
            case 5:
                printf("\nInserisci Codice Fiscale: ");
                scanf("%s", cf);
                printf("Cancellazione dell'appuntamento in corso, attendere.\n");
                cancellaAppuntamento(cf);
                system("PAUSE");
                break;
            case 6:
                concretizzaTamponi();
                printf("\nGrazie per aver usato il sistema, a presto!\n");
                system("PAUSE");
                exit(1);
            default:
                printf("Operazione non valida, riprovare\n");
                system("PAUSE");
                break;
        }
    }
}

/* Funzione per la piattaforma
Parametri:
Ritorna:
*/
void piattaforma(){
    appuntamento *positivi = creaListaPositivi();
    if(positivi == NULL){
        printf("\nNon ci sono positivi, fortunatamente!\n");
    }
    else{
        stampaPositivi(positivi);
    }
    printf("\n");
    system("PAUSE");
    return;
}
