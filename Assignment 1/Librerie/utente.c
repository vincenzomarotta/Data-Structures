#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "utente.h"
#include "menu.h"
#include "appuntamento.h"
#include "piattaforma.h"
#include "laboratorio.h"

/* Funzione che crea la lista di utenti da file
Parametri:
Ritorno: Lista di Utenti
*/
utente *creaListaUtenti(){
    utente *listaUtenti = NULL;

    FILE *loginUtente;

    // Apro il file dove conservo i dati degli utenti in modalità lettura
    loginUtente = fopen(FILE_UTENTI_LOGIN, "r");

    if(loginUtente == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return listaUtenti;
    }

    char riga[100];
    // Scorro il file finchè non finisce
    while(fgets(riga, 100, loginUtente) != NULL){
        // Utente temporaneo da inserire in lista
        utente u;
        u = azzeraUtente(u);
        // Indice di scorrimento della riga
        int i = 0;
        // Indice di appoggio temporaneo per ricordarmi da dove iniziare a prenere le parole
        int tmp;
        // Indice temporaneo per scorrere l'array di caratteri nelle struct
        int index;

        // Recupero Codice Fiscale
        // Prendo i primi 15 caratteri della riga, cioè il codice fiscale
       // printf("u.cf prima di iniziare tutto = %s\n", u.cf);
        for(i; i<16;i++){
            u.cf[i] = riga[i];
        }
        // Porto 'i' dopo lo spazio
        i++;

        // Recupero password
        // Conservo il valore di 'i' così so da dove ripartire
        tmp = i;
        // Scorro la riga finchè non trovo uno spazio
        while(riga[i] != ' '){
            i++;
        }

        // Utilizzo index per inserire i caratteri nella stringhe della struct
        index = 0;
        // Parto dal vecchio valore di 'i' e mi fermo al nuovo, cosi' recupero la paswword
        for(tmp; tmp<i; tmp++){
            u.password[index] = riga[tmp];
            index++;
        }
        // Porto 'i' dopo lo spazio
        i++;

        // Processo simile anche per gli altri campi dell'utente

        // Recupero nome
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            u.nome[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero cognome
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            u.cognome[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero data di nascita
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            u.dataNascita[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero numero telefono
        tmp = i;
        // Dato che questo è l'ultimo elemento della mia riga mi fermo al carattere di terminazione e non più allo spazio
        while(riga[i+1] != '\0'){
            i++;
        }

        index = 0;
        for(tmp; tmp<i; tmp++){
            u.telefono[index] = riga[tmp];
            index++;
        }

        // Aggiungo l'utente alla lista
        listaUtenti = inserisciUtenteInCoda(listaUtenti, u);
        // Azzero i campi della variabile utente
        u = azzeraUtente(u);
        memset((void*)riga, 0, 100);
    }
    // Chiudo il file e ritorno la lista
    fclose(loginUtente);
    return listaUtenti;
}

/* Funzione che azzera i campi dell'utente
Parametri: Utente
Ritorno: Utente aggiornato
*/
utente azzeraUtente(utente u){
    memset((void*)u.cf, 0, 17);
    memset((void*)u.nome, 0, 30);
    memset((void*)u.cognome, 0, 30);
    memset((void*)u.password, 0, 30);
    memset((void*)u.dataNascita, 0, 11);
    memset((void*)u.telefono, 0, 11);

    return u;
}

/* Funzione che inserisce l'utente in coda in maniera ricorsiva
Parametri: Lista di Utenti e un utente
Ritorno: Lista di Utenti aggiornata
*/
utente *inserisciUtenteInCoda(utente *lista, utente u){
    // Se La lista è vuota inserisce l'elemento
    if(lista == NULL){
        utente *lista = (utente *)malloc(sizeof(utente));
        lista->next = NULL;
        strcpy(lista->cf, u.cf);
        strcpy(lista->password, u.password);
        strcpy(lista->nome, u.nome);
        strcpy(lista->cognome, u.cognome);
        strcpy(lista->dataNascita, u.dataNascita);
        strcpy(lista->telefono,u.telefono);
        return lista;
    }
    // Chiamata ricorsiva
    else{
        lista->next = inserisciUtenteInCoda(lista->next, u);
    }
    return lista;
}

/* Funzione che stampa lista di utenti
Parametri: lista di utenti
Ritorna:
*/
void stampaListaUtenti(utente *lista){
    // Se lista vuota ritorna
    if(lista == NULL){
        return;
    }
    else{
        //Stampa dei campi
        printf("\nNome: %s\n", lista->nome);
        printf("Cognome: %s\n", lista->cognome);
        printf("Codice Fiscale: %s\n", lista->cf);
        printf("Password: %s\n", lista->password);
        printf("Data di Nascita: %s\n", lista->dataNascita);
        printf("Telefono: %s\n",lista->telefono);
        printf("============================================\n");
        //Chiamata ricorsiva
        stampaListaUtenti(lista->next);
    }
}

/* Funzione che inizializza i campi di un utente
Parametri:
Ritorna: Utente
*/
utente inizializzaUtente(){
    utente u;

    // Inserimento del Codice Fiscale
    printf("Inserisci Codice Fiscale (16 CARATTERI): ");
    scanf("%s", u.cf);
    while(strlen(u.cf)!=16){
        printf("Codice Fiscale errato, riprova: ");
        scanf("%s", u.cf);
    }

    for(int i=0; i<16;i++){
        u.cf[i] = toupper(u.cf[i]);
    }

    // Inserimento della password
    printf("Inserisci nuova Password (MAX 30 CARATTERI): ");
    scanf("%s", u.password);

    while(strlen(u.password) > 30){
        printf("Password troppo lunga, riprova: ");
        scanf("%s", u.password);
    }

    // Inserimento del nome
    printf("Inserisci Nome (MAX 30 CARATTERI): ");
    scanf("%s", u.nome);

    while(strlen(u.nome) > 30 || !isAllAlpha(u.nome,strlen(u.nome))){
        printf("Formato nome non corretto, riprova: ");
        scanf("%s", u.nome);
    }

    // Inserimento del cognome
    printf("Inserisci Cognome (MAX 30 CARATTERI): ");
    scanf("%s", u.cognome);

    while(strlen(u.cognome) > 30 || !isAllAlpha(u.cognome,strlen(u.cognome))){
        printf("Formato cognome non corretto, riprova: ");
        scanf("%s", u.cognome);
    }

    // Inserimento del data nascita
    printf("Inserisci Data di Nascita (FORMATO GG/MM/AAAA): ");
    scanf("%s", u.dataNascita);

    while(strlen(u.dataNascita) > 11 || !checkCorrettezzaData(u.dataNascita)){
        printf("Formato data nascita errato, riprova: ");
        scanf("%s", u.password);
    }

    // Inserimento del numero di telefono
    printf("Inserisci numero di telefono (MAX 10 CARATTERI): ");
    scanf("%s", u.telefono);

    while(strlen(u.telefono) > 11 || !isAllDigit(u.telefono, strlen(u.telefono))){
        printf("Formato del numero di telefono non corretto, riprova: ");
        scanf("%s", u.telefono);
    }

    return u;
}

/* Funzione che aggiunge un utente al file
Parametri:
Ritorna:
*/
void aggiungiUtente(){
    utente u;
    system("cls");
    printf("\t\t\t---- REGISTRAZIONE UTENTE ----\n\n");
    u = inizializzaUtente();

    FILE *loginUtenti;
    // Apertura del file in append
    loginUtenti = fopen(FILE_UTENTI_LOGIN,"a");

    if(loginUtenti == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return;
    }

    //Scrittura del nuovo utente
    fprintf(loginUtenti, "\n%s %s %s %s %s %s ", u.cf, u.password, u.nome, u.cognome, u.dataNascita, u.telefono);
    fclose(loginUtenti);
}

/* Funzione che controlla che i dati inseriti siano corretti
Parametro:
Ritorna:
*/
void checkLoginUtente(){
    system("cls");
    char cf[17], password[30];
    printf("\t\t\t---- LOGIN UTENTE ----\n\n");
    // Prendo in input i dati dell'utente
    printf("Inserisci Codice Fiscale: ");
    scanf("%s", cf);

    for(int i=0; i<16;i++){
        cf[i] = toupper(cf[i]);
    }

    printf("Inserisci Passowrd: ");
    scanf("%s", password);

    // Recupero gli utenti dal file così controllo se i dati sono corretti
    utente *listaUtenti = NULL;
    listaUtenti = creaListaUtenti();

    // Controllo la correttezza dei dati in input
    while(listaUtenti!=NULL){
        if(!strcasecmp(cf,listaUtenti->cf)){
            if(!strcmp(password,listaUtenti->password)){
                // Se dati sono corretti apro il menù utente
                printf("\nAccesso effettuato correttamente!\n");
                system("PAUSE");
                menuUtente(cf);
                return;
            }
        }
        listaUtenti = listaUtenti->next;
    }

    // Se i dati non sono corretti l'utente può tornare al menù principale o riprovare ad inserire i dati
    printf("Codice Fiscale o Password errati.\n");
    int scelta;
    while(1){
        printf("\n1. Torna al menu' principale.\n2. Riprova.\n");
        printf("Inserisci opzione: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                return;
            case 2:
                checkLoginUtente();
            default:
                printf("Opzione non valida.\n");
                break;
        }
    }
}

/* Funzione che recupera l'ultimo esito di un tampone di un determinato utente
Parametri: Codice Fiscale utente
Ritorna:
*/
void recuperaEsitoUtente(char cf[]){
    char codiceFiscale[17];
    strcpy(codiceFiscale,cf);

    if(!storicoPresente(codiceFiscale)){
        printf("\nNon e' presente nessun esito recente.\n\n");
        system("PAUSE");
        return;
    }

    appuntamento *storico = creaStoricoAppuntamento();
    appuntamento *head = storico;
    
    while(storico->next != head){
        storico = storico->next;
    }

    while(storico != head){
        if(!strcmp(storico->cf, codiceFiscale)){
            printf("\nIL TAMPONE DEL GIORNO %d HA DATO COME ESITO %s\n\n", storico->giorno, storico->esitoTampone);
            system("PAUSE");
            return;
        }
        storico = storico->prev;
    }
    if(!strcmp(storico->cf, codiceFiscale)){
        printf("\nIL TAMPONE DEL GIORNO %d HA DATO COME ESITO %s\n\n", storico->giorno, storico->esitoTampone);
        system("PAUSE");
        return;
    }
}

/* Controlla che i valori sono tutti numeri
Parametri: stringa e relativa lungehzza
Ritorna: boolean
*/
boolean isAllDigit(char stringa[], int len){
    for(int i=0; i<len; i++){
        if(!isdigit(stringa[i])){
            return false;
        }
    }
    return true;
}

/* Controlla che i valori siano tutti caratteri
Parametri: stringa e relativa lunghezza
Ritorna: boolean
*/
boolean isAllAlpha(char stringa[], int len){
    for(int i=0; i<len; i++){
        if(isdigit(stringa[i])){
            return false;
        }
    }
    return true;
}

/* Controlla la correttezza della data di nascita
Parametri: stringa data di nascita
Ritorna: boolean
*/
boolean checkCorrettezzaData(char dataNascita[]){
    if(strlen(dataNascita)!=10){
        return false;
    }

    if(!isdigit(dataNascita[0]) && !isdigit(dataNascita[1]) && !isdigit(dataNascita[3]) && !isdigit(dataNascita[4]) && !isdigit(dataNascita[6]) && !isdigit(dataNascita[7]) 
        && !isdigit(dataNascita[8]) && !isdigit(dataNascita[9])){
        return false;
    }
    else{
        return true;
    }

}
