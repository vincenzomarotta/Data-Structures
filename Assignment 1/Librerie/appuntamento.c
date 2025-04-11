#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "appuntamento.h"
#include "menu.h"
#include "utente.h"
#include "piattaforma.h"
#include "laboratorio.h"


/* Funzione che recupera gli appuntamenti da file
Parametri:
Ritorna: puntatore a lista di appuntamenti
*/
appuntamento *creaListaAppuntamenti(){
    // Creo lista di appuntamenti
    appuntamento *listaAppuntamenti = NULL;

    // Apro il file in lettura
    FILE *prenotazioneAppuntamenti;
    prenotazioneAppuntamenti = fopen(FILE_PRENOTAZIONE_APPUNTAMENTI, "r");

    if(prenotazioneAppuntamenti == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return listaAppuntamenti;
    }

    char riga[100];

    //Scorro il file finchè non è vuoto
    while(fgets(riga, 100, prenotazioneAppuntamenti) != NULL){
        // Creo variabile appuntamento
        appuntamento a;
        a = azzeraAppuntamento(a);

        // Indici per scorrimento della riga
        int i = 0;
        int tmp = 0; // Temporaneo per ricordare da dove inizia la parola
        int index = 0; // Scorrere l'array delle struct

        // Recupero id
        char idApp[20];
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            idApp[index] = riga[tmp];
            index++;
        }
        a.id = atoi(idApp);
        i++;

        // Recupero codice fiscale
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            a.cf[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero giorno
        char day[20];
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            day[index] = riga[tmp];
        }

        a.giorno = atoi(day);
        i++;


        // Recupero orario
        char ora[20];
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i;tmp++){
            ora[index] = riga[tmp];
            index++;
        }

        strcpy(a.orario,ora);
        i++;

        // Recupero sintomi
        a.descrizioneSintomi = riga[i];
        i = i+2;

        // Recupero esito tampone
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            a.esitoTampone[index] = riga[tmp];
            index++;
        }


        listaAppuntamenti = inserisciAppuntamentiInCoda(listaAppuntamenti, a);
        // rialloco memoria
        a = azzeraAppuntamento(a);
        memset((void *)day, 0, 20);
        memset((void *)idApp, 0, 20);
        memset((void *)ora, 0, 20);
    }
    fclose(prenotazioneAppuntamenti);
    return listaAppuntamenti;
}

/* Funzione che aggiunge gli appuntamenti in coda
Parametri: Lista e appuntamento
Ritorna: lista
*/
appuntamento *inserisciAppuntamentiInCoda(appuntamento *lista, appuntamento a){
    if(lista == NULL){
        lista = (appuntamento*)malloc(sizeof(appuntamento));
        strcpy(lista->cf,a.cf);
        strcpy(lista->orario,a.orario);
        lista->descrizioneSintomi = a.descrizioneSintomi;
        lista->id = a.id;
        strcpy(lista->esitoTampone, a.esitoTampone);
        lista->giorno = a.giorno;
        lista->next = lista;
        lista->prev = lista;

        return lista;
    }
    else{
        appuntamento *scorri = (appuntamento *)malloc(sizeof(appuntamento));
        scorri = lista;

        while(scorri->next != lista){
            scorri = scorri->next;
        }

        appuntamento *tmp = (appuntamento *)malloc(sizeof(appuntamento));
        strcpy(tmp->cf,a.cf);
        strcpy(tmp->orario,a.orario);
        tmp->descrizioneSintomi = a.descrizioneSintomi;
        tmp->id = a.id;
        strcpy(tmp->esitoTampone, a.esitoTampone);
        tmp->giorno = a.giorno;
        tmp->prev = scorri;
        tmp->next = lista;
        scorri->next = tmp;

        return lista;
    }
}

/* Funzione che azzera i campi del variabile appuntamento
Parametri: appuntamento
Ritorna: appuntamento aggiornato
*/
appuntamento azzeraAppuntamento(appuntamento a){
    memset((void *)a.cf, 0, 17);
    memset((void *)a.esitoTampone, 0, 20);
    memset((void *) a.orario, 0, 20);
    return a;
}

/* Funzione che inserisce in coda le richieste di appuntamenti
Parametri: Lista di appuntamenti e l'appuntamento da inserire
Ritorna: Lista aggiornata
*/
appuntamento *inserisciRichiesteInCoda(appuntamento *lista, appuntamento a){
    if(lista == NULL){
        appuntamento *lista = (appuntamento *)malloc(sizeof(appuntamento));
        lista->next = NULL;
        strcpy(lista->cf, a.cf);
        lista->descrizioneSintomi = a.descrizioneSintomi;
        return lista;
    }
    // Chiamata ricorsiva
    else {
        lista->next = inserisciRichiesteInCoda(lista->next, a);
    }
    return lista;
}

/* Funzione che crea una richiesta per effettuare un tampone
Parametro: codice fiscale di chi deve ricevere il tampone
Ritorna: appuntamento
*/
void richiediAppuntamento(char cf[], char sintomi){
    appuntamento a;
    strcpy(a.cf, cf);

    if(appuntamentoPresente(a.cf)){
        printf("\nHai gia' effettuato una prenotazione. \n");
        return;
    }

    // Prendo in input la tipologia di sintomi dell'utente
    sintomi = toupper(sintomi);

    if(sintomi != 'A' && sintomi != 'B' && sintomi != 'C' && sintomi != 'D'){
        printf("\nInserisci un valore valido.\n");
        system("PAUSE");
        return;
    }
    a.descrizioneSintomi = sintomi;

    FILE *richieste;

    // Scrivo tutto su un file per le richieste
    richieste = fopen(FILE_RICHIESTE_APPUNTAMENTI, "a");
    if(richieste == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return;
    }
    fprintf(richieste, "%s %c \n", a.cf, a.descrizioneSintomi);
    fclose(richieste);
    return;
}

/* Funzione che recupera da file le richieste di appuntamento e le ordina: prima i sintomatici, e poi gli asintomatici.
Parametri:
Ritorna: lista di richieste di appuntamento
*/
appuntamento *creaListaRichieste(){
    appuntamento *listaSintomatici = NULL;
    appuntamento *listaAsintomatici = NULL;
    appuntamento *listaRichieste = NULL;

    FILE* richieste;
    richieste = fopen(FILE_RICHIESTE_APPUNTAMENTI, "r");

    if(richieste == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return listaRichieste;
    }

    char riga[50];

    while(fgets(riga, 50, richieste) != NULL){
        appuntamento a;
        a = azzeraAppuntamento(a);

        // Indice temporaneo per recuperare cf e sintomi
        int i=0;

        //Recupero cf
        for(i; i<16; i++){
            a.cf[i] = riga[i];
        }
        i++;

        a.descrizioneSintomi = riga[i];

        if(a.descrizioneSintomi == 'D'){
            listaAsintomatici = inserisciRichiesteInCoda(listaAsintomatici, a);
        }
        else{
            listaSintomatici = inserisciRichiesteInCoda(listaSintomatici, a);
        }

        a = azzeraAppuntamento(a);

    }

    fclose(richieste);

    if(listaSintomatici == NULL && listaAsintomatici != NULL){
        return listaAsintomatici;
    }
    else if(listaSintomatici != NULL && listaAsintomatici == NULL){
        return listaSintomatici;
    }
    else if(listaSintomatici == NULL && listaAsintomatici == NULL){
        return listaRichieste;
    }

    // Unisco le due liste
    appuntamento *tmp;
    tmp = listaSintomatici;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = listaAsintomatici;

    listaRichieste = listaSintomatici;

    return listaRichieste;
}

/* Funzione che controlla se c'è una richiesta già presente di un utente
Parametri: codice fiscale
Ritorna: booelan
*/
boolean richiestaPresente(char cf[]){
    appuntamento *richieste = creaListaRichieste();

    if(richieste == NULL){
        return false;
    }
    appuntamento *head = richieste;
    if(!strcmp(richieste->cf,cf)){
        return true;
    }
    else{
        richieste = richieste->next;
        while(richieste != head){
            if(!strcmp(richieste->cf,cf)){
                return true;
            }
            richieste = richieste->next;
        }
        return false;
    }
}

/* Funzione che stampa le richieste di appuntamento per farle visualizzare al medico
Parametri: Lista di richieste di appuntamento
Ritorna:
*/
void stampaRichiesteAppuntamento(appuntamento *lista){
    if(lista == NULL){
        return;
    }
    else{
        printf("Codice Fiscale: %s\n",lista->cf);
        printf("Tipologia Sintomi: %c", lista->descrizioneSintomi);
        printf("\n=================================\n");
        stampaRichiesteAppuntamento(lista->next);
    }
}

/* Funzione che crea gli appuntamenti in coda di richiesta
Parametri: Lista di richieste
Ritorna:
*/
appuntamento *creaAppuntamenti(appuntamento *listaAppuntamenti, appuntamento *listaRichieste){

    while(listaRichieste != NULL){
        appuntamento a;
        a = azzeraAppuntamento(a);

        appuntamento *tmp = (appuntamento *)malloc(sizeof(appuntamento));
        tmp = listaAppuntamenti;

        if (listaAppuntamenti == NULL){
            a = recuperaUltimiValori(a);
            strcpy(a.esitoTampone, "Elaborazione");
            // Copio il codice fiscale
            strcpy(a.cf, listaRichieste->cf);
            // Copio tipologia sintomi
            a.descrizioneSintomi = listaRichieste->descrizioneSintomi;
        }
        else{
            while(tmp->next != listaAppuntamenti){
                tmp = tmp->next;
            }

            // Inserimento nuovo ID
            a.id = tmp->id + 1;

            // Tampone in elaborazione
            strcpy(a.esitoTampone, "Elaborazione");
            // Copio il codice fiscale
            strcpy(a.cf, listaRichieste->cf);
            // Copio tipologia sintomi
            a.descrizioneSintomi = listaRichieste->descrizioneSintomi;

            // Scelgo il giorno e l'orario
            if(tmp == listaAppuntamenti){
                strcpy(a.orario,"Mattina");
                a.giorno = tmp->giorno;
            }
            else if(!strcmp(tmp->orario,"Mattina")){
                if(!strcmp(tmp->prev->orario,"Mattina")){
                    strcpy(a.orario,"Pomeriggio");
                    a.giorno = tmp->giorno;
                }
                else{
                    strcpy(a.orario,"Mattina");
                    a.giorno = tmp->giorno;
                }
            }
            else if(!strcmp(tmp->orario,"Pomeriggio")){
                if(!strcmp(tmp->prev->orario,"Mattina")){
                    strcpy(a.orario,"Pomeriggio");
                    a.giorno = tmp->giorno;
                }
                else{
                    strcpy(a.orario,"Sera");
                    a.giorno = tmp->giorno;
                }
            }
            else{
                if(!strcmp(tmp->prev->orario,"Pomeriggio")){
                    strcpy(a.orario,"Sera");
                    a.giorno = tmp->giorno;
                }
                else{
                    strcpy(a.orario,"Mattina");
                    a.giorno = tmp->giorno + 1;
                }
            }
        }

        // Inserisco appuntamenti in lista
        listaAppuntamenti = inserisciAppuntamentiInCoda(listaAppuntamenti, a);

        a = azzeraAppuntamento(a);
        // Continuo con le richieste
        listaRichieste = listaRichieste->next;

    }

    return listaAppuntamenti;
}

/* Funzione che fissa ed inserisce i nuovi appuntamenti nel file
Parametri: Lista delle richieste
Ritorna:
*/
void fissaAppuntamenti(appuntamento *listaRichieste){
    if(listaRichieste == NULL){
        printf("\nNon ci sono appuntamenti richiesti.\n");
        system("PAUSE");
        return;
    }

    printf("\t\t\t---- FISSO APPUNTAMENTI ----\n\n");
    appuntamento *listaAppuntamenti = NULL;
    listaAppuntamenti = creaListaAppuntamenti();

    // Accetto le richieste di tampone facendole diventare degli appuntamenti
    listaAppuntamenti = creaAppuntamenti(listaAppuntamenti, listaRichieste);

    FILE *appuntamenti;
    appuntamenti = fopen(FILE_PRENOTAZIONE_APPUNTAMENTI,"w");

    appuntamento *head = listaAppuntamenti;
    // Scrivo su file gli appuntamenti
    fprintf(appuntamenti,"%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
    listaAppuntamenti = listaAppuntamenti->next;
    while(listaAppuntamenti != head){
        fprintf(appuntamenti,"\n%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
        listaAppuntamenti = listaAppuntamenti->next;
    }

    fclose(appuntamenti);

    // Svuoto il file delle richieste
    FILE *richieste;
    richieste = fopen(FILE_RICHIESTE_APPUNTAMENTI, "w");
    fclose(richieste);
}

/* Funzione che stammpa la lista degli appuntamenti
Parametri: Lista di appuntamenti
Ritorna:
*/
void stampaAppuntamenti(appuntamento *listaAppuntamenti){
    if(listaAppuntamenti == NULL){
        printf("\nNon ci sono appuntamenti da visualizzare.\n\n");
        system("PAUSE");
        return;
    }
    system("cls");
    appuntamento *testa = listaAppuntamenti;
    printf("ID Appuntamento: %d\n",listaAppuntamenti->id);
    printf("Codice Fiscale paziente: %s\n",listaAppuntamenti->cf);
    printf("Numero Giorno: %d\n",listaAppuntamenti->giorno);
    printf("Orario: %s\n",listaAppuntamenti->orario);
    printf("Tipologia Sintomi: %c\n",listaAppuntamenti->descrizioneSintomi);
    printf("Esito Tampone: %s\n", listaAppuntamenti->esitoTampone);
    printf("=========================\n");
    listaAppuntamenti = listaAppuntamenti->next;
    while(listaAppuntamenti!=testa){
        printf("ID Appuntamento: %d\n",listaAppuntamenti->id);
        printf("Codice Fiscale paziente: %s\n",listaAppuntamenti->cf);
        printf("Numero Giorno: %d\n",listaAppuntamenti->giorno);
        printf("Orario: %s\n",listaAppuntamenti->orario);
        printf("Tipologia Sintomi: %c\n",listaAppuntamenti->descrizioneSintomi);
        printf("Esito Tampone: %s\n", listaAppuntamenti->esitoTampone);
        printf("=========================\n");
        listaAppuntamenti= listaAppuntamenti->next;
    }

    printf("\n");
    system("PAUSE");
}

/* Funzione per controllare se un utente ha già richiesto un appuntamento
Parametri: Codice fiscale utente
Ritorna: Boolean
*/
boolean appuntamentoPresente(char cf[]){
    appuntamento *lista = creaListaAppuntamenti();
    appuntamento *head = lista;

    if(lista == NULL){
        return false;
    }

    // Controllo in testa
    if(!strcmp(lista->cf,cf)){
        return true;
    }
    else{
        lista = lista->next;
        while(lista != head){
            if(!strcmp(lista->cf,cf)){
                return true;
            }
            lista = lista->next;
        }
        return false;
    }
}

/* Funzione che stampa appuntamento dell'utente
Parametri: Codice Fiscale
Riorna:
*/
void visualizzaAppuntamentoUtente(char cf[]){

    if(!appuntamentoPresente(cf)){
        printf("\nAppuntamento non presente.\n\n");
        system("PAUSE");
        return;
    }

    appuntamento *lista = creaListaAppuntamenti();
    appuntamento *head = lista;


    if(!strcmp(lista->cf,cf)){
        printf("\n\n---- ECCO I DETTAGLI DEL TUO APPUNTAMENTO: ----\n");
        printf("ID Appuntamento: %d\n", lista->id);
        printf("Giorno: %d\n", lista->giorno);
        printf("Orario: %s\n\n", lista->orario);
        system("PAUSE");
        return;
    }
    else{
        lista = lista->next;
        while(lista != head){
            if(!strcmp(lista->cf,cf)){
                printf("\n\n---- ECCO I DETTAGLI DEL TUO APPUNTAMENTO: ----\n");
                printf("ID Appuntamento: %d\n", lista->id);
                printf("Giorno: %d\n", lista->giorno);
                printf("Orario: %s\n\n", lista->orario);
                system("PAUSE");
                return;
            }
            lista = lista->next;
        }
        printf("\nAppuntamento non presente.\n\n");
        system("PAUSE");
        return;
    }
}

/* Funzione che permette al dipendente di aggiungere un singolo appuntamento
Parametri: Codice Fiscale
Ritorna:
*/
void aggiungiAppuntamento(char cf[], char sintomi){

    if(appuntamentoPresente(cf)){
        printf("\nL'utente ha gia' effettuato una prenotazione.\n");
        system("PAUSE");
        return;
    }

    if(strlen(cf) != 16){
        printf("\nCodice Fiscale non valido.\n");
        system("PAUSE");
        return;
    }

    sintomi = toupper(sintomi);
    if(sintomi != 'A' && sintomi != 'B' && sintomi != 'C' && sintomi != 'D'){
        printf("\nInserisci un valore valido.\n");
        system("PAUSE");
        return;
    }

    printf("\t\t\t---- AGGIUNGI APPUNTAMENTO ----\n\n");

    for(int i=0; i<16;i++){
        cf[i] = toupper(cf[i]);
    }

    appuntamento a;
    a = azzeraAppuntamento(a);
    strcpy(a.cf, cf);
    a.descrizioneSintomi = sintomi;

    appuntamento *listaAppuntamenti = creaListaAppuntamenti();

    appuntamento *tmp = (appuntamento *)malloc(sizeof(appuntamento));
    tmp = listaAppuntamenti;

    if(tmp == NULL){
        a = recuperaUltimiValori(a);
        strcpy(a.esitoTampone, "Elaborazione");
    }
    else {
        while(tmp->next != listaAppuntamenti){
            tmp = tmp->next;
        }

        // Inserimento nuovo ID
        a.id = tmp->id + 1;

        // Tampone in elaborazione
        strcpy(a.esitoTampone, "Elaborazione");

        // Scelgo il giorno e l'orario
        if(tmp == listaAppuntamenti){
            strcpy(a.orario,"Mattina");
            a.giorno = tmp->giorno;
        }
        else if(!strcmp(tmp->orario,"Mattina")){
            if(!strcmp(tmp->prev->orario,"Mattina")){
                strcpy(a.orario,"Pomeriggio");
                a.giorno = tmp->giorno;
            }
            else{
                strcpy(a.orario,"Mattina");
                a.giorno = tmp->giorno;
            }
        }
        else if(!strcmp(tmp->orario,"Pomeriggio")){
            if(!strcmp(tmp->prev->orario,"Mattina")){
                strcpy(a.orario,"Pomeriggio");
                a.giorno = tmp->giorno;
            }
            else{
                strcpy(a.orario,"Sera");
                a.giorno = tmp->giorno;
            }
        }
        else{
            if(!strcmp(tmp->prev->orario,"Pomeriggio")){
                strcpy(a.orario,"Sera");
                a.giorno = tmp->giorno;
            }
            else{
                strcpy(a.orario,"Mattina");
                a.giorno = tmp->giorno + 1;
            }
        }
    }

    // Inserisco appuntamenti in lista
    listaAppuntamenti = inserisciAppuntamentiInCoda(listaAppuntamenti, a);

    FILE *appuntamenti;
    appuntamenti = fopen(FILE_PRENOTAZIONE_APPUNTAMENTI,"w");
    appuntamento *head = listaAppuntamenti;
    // Scrivo su file gli appuntamenti
    fprintf(appuntamenti,"%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
    listaAppuntamenti = listaAppuntamenti->next;
    while(listaAppuntamenti != head){
        fprintf(appuntamenti,"\n%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
        listaAppuntamenti = listaAppuntamenti->next;
    }

    fclose(appuntamenti);

    printf("\nAppuntamento aggiunto.\n");
    printf("Giorno: %d\n", a.giorno);
    printf("Orario: %s\n\n",a.orario);
    printf("==========================\n");
    system("PAUSE");

}

/* Funzione per cancellare gli appuntamenti
Parametri: Codice Fiscale
Ritorna:
*/
void cancellaAppuntamento(char cf[]){

    if(!appuntamentoPresente(cf)){
        printf("\nAppuntamento di - %s - non presente.\n", cf);
        return;
    }

    appuntamento *listaAppuntamenti = creaListaAppuntamenti();
    appuntamento *tmp = listaAppuntamenti;

    if(!strcmp(tmp->cf,cf)){
        listaAppuntamenti = listaAppuntamenti->next;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }
    else{
        tmp = tmp->next;
        while(tmp != listaAppuntamenti){
            if(!strcmp(tmp->cf,cf)){
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free(tmp);
                break;
            }
            tmp = tmp->next;
        }
    }

    FILE *appuntamenti;
    appuntamenti = fopen(FILE_PRENOTAZIONE_APPUNTAMENTI,"w");

    if(listaAppuntamenti == NULL || listaAppuntamenti->id == tmp->id){
        fclose(appuntamenti);
        return;
    }

    appuntamenti = fopen(FILE_PRENOTAZIONE_APPUNTAMENTI,"w");

    appuntamento *head = listaAppuntamenti;
    // Riscrivo su file gli appuntamenti
    fprintf(appuntamenti,"%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
    listaAppuntamenti = listaAppuntamenti->next;
    while(listaAppuntamenti->next != head){
        fprintf(appuntamenti,"\n%d %s %d %s %c %s ", listaAppuntamenti->id, listaAppuntamenti->cf, listaAppuntamenti->giorno, listaAppuntamenti->orario, listaAppuntamenti->descrizioneSintomi, listaAppuntamenti->esitoTampone);
        listaAppuntamenti = listaAppuntamenti->next;
    }

    fclose(appuntamenti);
    return;
}

/* Funzione che concretizza i tamponi
Parametri:
Ritorna:
*/
void concretizzaTamponi(){
    int giorno;
    char codF[17];
    char sint;
    appuntamento *listaAppuntamenti = creaListaAppuntamenti();
    if(listaAppuntamenti == NULL){
        printf("\nNon ci sono tamponi da concretizzare.\n");
        return;
    }

    srand(time(NULL));
    // Recupero il primo giorno
    giorno = listaAppuntamenti->giorno;
    appuntamento *positivi = NULL;
    int esito;

    while(listaAppuntamenti != NULL && listaAppuntamenti->giorno == giorno){
        memset((void*)listaAppuntamenti->esitoTampone,0,20);
        memset((void*)codF,0,17);

        esito = rand()%2;
        // Se 0 è negativo, se 1 è positivo
        if(esito == 0){
            strcpy(listaAppuntamenti->esitoTampone,"Negativo");
            strcpy(codF,listaAppuntamenti->cf);
            aggiungiStorico(listaAppuntamenti);
            cancellaAppuntamento(codF);
            cancellaPositivo(codF);
        }
        else{
            strcpy(listaAppuntamenti->esitoTampone,"Positivo");
            strcpy(codF,listaAppuntamenti->cf);
            sint = listaAppuntamenti->descrizioneSintomi;
            aggiungiStorico(listaAppuntamenti);
            cancellaAppuntamento(codF);
            richiediAppuntamento(codF,sint);
            aggiungiPositivo(codF, sint);
        }

        free(listaAppuntamenti);
        listaAppuntamenti = creaListaAppuntamenti();

    }

    printf("\nI tamponi in attesa sono stati concretizzati.\n");
}

/* Funzione che aggiunge lo storico dei tamponi effettuati
Parametri: Appuntamento
Ritorna:
*/
void aggiungiStorico(appuntamento *a){
    FILE *storico;
    storico = fopen(FILE_STORICO_TEST,"a");

    fprintf(storico,"%d %s %d %s %c %s \n", a->id, a->cf, a->giorno, a->orario, a->descrizioneSintomi, a->esitoTampone);
    fclose(storico);

    // Cambio i valori all'interno del file che contiene gli ultimi valori
    FILE *valori;
    valori = fopen(FILE_ULTIMI_VALORI,"w");
    fprintf(valori,"%d %d ",a->id, a->giorno);
    fclose(valori);
}

/* Funzione che crea lista storico appuntamenti
Parametri:
Ritorna: lista storico
*/
appuntamento *creaStoricoAppuntamento(){
    // Creo lista di appuntamenti
    appuntamento *listaAppuntamenti = NULL;

    // Apro il file in lettura
    FILE *storico;
    storico = fopen(FILE_STORICO_TEST, "r");

    if(storico == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return listaAppuntamenti;
    }

    char riga[100];

    //Scorro il file finchè non è vuoto
    while(fgets(riga, 100, storico) != NULL){
        // Creo variabile appuntamento
        appuntamento a;
        a = azzeraAppuntamento(a);

        // Indici per scorrimento della riga
        int i = 0;
        int tmp = 0; // Temporaneo per ricordare da dove inizia la parola
        int index = 0; // Scorrere l'array delle struct

        // Recupero id
        char idApp[20];
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            idApp[index] = riga[tmp];
            index++;
        }
        a.id = atoi(idApp);
        i++;

        // Recupero codice fiscale
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            a.cf[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero giorno
        char day[20];
        tmp = i;
        while(riga[i]!=' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            day[index] = riga[tmp];
        }

        a.giorno = atoi(day);
        i++;


        // Recupero orario
        char ora[20];
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i;tmp++){
            ora[index] = riga[tmp];
            index++;
        }

        strcpy(a.orario,ora);
        printf("AOOOOOOOOOOOOOOOO : %s\n", a.orario);
        i++;

        // Recupero sintomi
        a.descrizioneSintomi = riga[i];
        i = i+2;

        // Recupero esito tampone
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            a.esitoTampone[index] = riga[tmp];
            index++;
        }


        listaAppuntamenti = inserisciAppuntamentiInCoda(listaAppuntamenti, a);
        a = azzeraAppuntamento(a);
        memset((void *)day, 0, 20);
        memset((void *)idApp, 0, 20);
        memset((void *)ora, 0, 20);
    }

    fclose(storico);
    return listaAppuntamenti;
}

/* Funzione per recuperare gli ultimi valori se la lista delle prenotazioni è vuota
Parametri: Appuntamento
Ritorna: Appuntamento
*/
appuntamento recuperaUltimiValori(appuntamento a){
    FILE *ultimiValori;

    ultimiValori = fopen(FILE_ULTIMI_VALORI,"r");
    char riga[30];
    char id[12];
    char giorno[12];
    memset((void *)giorno,0,12);

    while(fgets(riga, 30, ultimiValori) != NULL){
        int i = 0;
        int index = 0;
        int tmp = 0;

        // Recupero ID Appuntamento
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            id[index] = riga[tmp];
            index++;
        }

        // Recupero Giorno
        i = i+1;
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }


        index = 0;
        for(tmp;tmp<i;tmp++){
            giorno[index] = riga[tmp];
            index++;
        }

    }
    a.id = atoi(id) + 1;
    a.giorno = atoi(giorno) + 1;
    strcpy(a.orario,"Mattina");

    fclose(ultimiValori);
    return a;
}

/* Funzione per controllare se un utente ha uno storico presente
Parametri: Codice fiscale utente
Ritorna: Boolean
*/
boolean storicoPresente(char cf[]){
    appuntamento *lista = creaStoricoAppuntamento();
    appuntamento *head = lista;

    if(lista == NULL){
        return false;
    }

    // Controllo in testa
    if(!strcmp(lista->cf,cf)){
        return true;
    }
    else{
        lista = lista->next;
        while(lista != head){
            if(!strcmp(lista->cf,cf)){
                return true;
            }
            lista = lista->next;
        }
        return false;
    }
}
