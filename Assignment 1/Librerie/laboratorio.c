#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "laboratorio.h"
#include "menu.h"
#include "utente.h"
#include "appuntamento.h"
#include "piattaforma.h"


/* Funzione che crea la lista di dipendenti da file
Parametri:
Ritorno: Lista di dipendenti
*/
dipendente *creaListaDipendenti(){
    dipendente *listaDipendenti = NULL;

    FILE *loginDipendente;

    // Apro il file dove conservo i dati dei dipendenti in modalità lettura
    loginDipendente = fopen(FILE_DIPENDENTI_LOGIN, "r");

    if(loginDipendente == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return listaDipendenti;
    }

    char riga[100];

    // Scorro il file finchè non finisce
    while(fgets(riga, 100, loginDipendente) != NULL){
        // Dipendente temporaneo da inserire nella lista
        dipendente d;
        d = azzeraDipendente(d);
        // Indice di scorrimento della riga
        int i = 0;
        // Indice di appoggio temporaneo per ricordarmi da dove iniziare a prenere le parole
        int tmp;
        // Indice temporaneo per scorrere l'array di caratteri nelle struct
        int index;

        //Recupero Codice Utente
        // Conservo il valore di 'i' così so da dove ripartire
        tmp = i;
        // Scorro la riga finchè non trovo uno spazio
        while(riga[i] != ' '){
            i++;
        }

        // Utilizzo index per inserire i caratteri nella stringhe della struct
        index = 0;
        // Parto dal vecchio valore di 'i' e mi fermo al nuovo, cosi' recupero il codice dipendente
        for(tmp;tmp<i;tmp++){
            d.codiceDipendente[index] = riga[tmp];
            index++;
        }
        // Porto i dopo lo spazio
        i++;

        // Processo simile anche per gli altri campi del dipendente
        // Recupero password
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            d.password[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero nome
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            d.nome[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero cognome
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            d.cognome[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero data di nascita
        tmp = i;
        while(riga[i] != ' '){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            d.dataNascita[index] = riga[tmp];
            index++;
        }
        i++;

        // Recupero numero di telefono
        tmp = i;
        // Dato che il numero è l'ultimo elemento della lista, mi fermo quando c'è il caratttere di terminazione
        while(riga[i+1] != '\0'){
            i++;
        }

        index = 0;
        for(tmp;tmp<i;tmp++){
            d.telefono[index] = riga[tmp];
            index++;
        }

        // Inserisco il dipendente nella lista
        listaDipendenti = inserisciDipendenteInCoda(listaDipendenti, d);
        // Azzero i campi della variabile dipendente
        d = azzeraDipendente(d);
        memset((void*)riga, 0, 100);
    }

    // Chiudo il file e ritorno la lista
    fclose(loginDipendente);
    return listaDipendenti;
}

/* Funzione che azzera i campi del dipendente
Parametri: Dipendente
Ritorno: Dipendente aggiornato
*/
dipendente azzeraDipendente(dipendente d){
    memset((void*)d.codiceDipendente, 0, 11);
    memset((void*)d.nome, 0, 30);
    memset((void*)d.cognome, 0, 30);
    memset((void*)d.password, 0, 30);
    memset((void*)d.dataNascita, 0, 11);
    memset((void*)d.telefono,0,11);
    return d;
}

/* Funzione che inizializza i campi di un dipendente
Parametri:
Ritorna: Dipendente
*/
dipendente inizializzaDipendente(){
    dipendente d;

    // Inserimento Codice Dipendente
    printf("Inserisci Codice Dipendente (10 CARATTERI): ");
    scanf("%s", d.codiceDipendente);
    while(strlen(d.codiceDipendente)!=10){
        printf("Codice Dipendente errato, riprova: ");
        scanf("%s", d.codiceDipendente);
    }

    // Inserimento della password
    printf("Inserisci nuova Password (MAX 30 CARATTERI): ");
    scanf("%s", d.password);

    while(strlen(d.password) > 30){
        printf("Password troppo lunga, riprova: ");
        scanf("%s", d.password);
    }

    // Inserimento del nome
    printf("Inserisci Nome (MAX 30 CARATTERI): ");
    scanf("%s", d.nome);

    while(strlen(d.nome) > 30 || !isAllAlpha(d.nome,strlen(d.nome))){
        printf("Formato nome errato, riprova: ");
        scanf("%s", d.nome);
    }

    // Inserimento del cognome
    printf("Inserisci Cognome (MAX 30 CARATTERI): ");
    scanf("%s", d.cognome);

    while(strlen(d.cognome) > 30 || !isAllAlpha(d.cognome, strlen(d.cognome))){
        printf("Formato cognome errato, riprova: ");
        scanf("%s", d.cognome);
    }

    // Inserimento del data nascita
    printf("Inserisci Data di Nascita(FORMATO GG/MM/AAAA): ");
    scanf("%s", d.dataNascita);

    while(strlen(d.dataNascita) > 11 || !checkCorrettezzaData(d.dataNascita)){
        printf("Formato data di nascita errato, riprova: ");
        scanf("%s", d.password);
    }

    // Inserimento del numero di telefono
    printf("Inserisci numero di telefono (MAX 10 CARATTERI): ");
    scanf("%s", d.telefono);

    while(strlen(d.telefono) > 11 || !isAllDigit(d.telefono, strlen(d.telefono))){
        printf("Formato numero di telefono errato, riprova: ");
        scanf("%s", d.telefono);
    }


    return d;
}

/* Funzione che aggiunge un dipendente al file
Parametri:
Ritorna:
*/
void aggiungiDipendente(){
    dipendente d;
    system("cls");
    printf("\t\t\t---- REGISTRAZIONE DIPENDENTE ----\n\n");
    d = inizializzaDipendente();

    FILE *loginDipedenti;
    // Apertura del file in append
    loginDipedenti = fopen(FILE_DIPENDENTI_LOGIN, "a");

    if(loginDipedenti == NULL){
        printf("Si e' verficato un errore nell'apertura del file nei nostri sistemi, ti prego di riprovare.\n");
        return;
    }

    // Scrittura del nuovo dipendente
    fprintf(loginDipedenti, "\n%s %s %s %s %s %s ", d.codiceDipendente, d.password, d.nome, d.cognome, d.dataNascita, d.telefono);
    fclose(loginDipedenti);
}

/* Funzione che inserisce il dipendente in coda in maniera ricorsiva
Parametri: Lista di dipendenti e un dipendente
Ritorno: Lista di dipendenti aggiornata
*/
dipendente *inserisciDipendenteInCoda(dipendente *lista, dipendente d){
    // Se lista nulla aggiungo il nuovo elemento in coda
    if(lista == NULL){
        dipendente *lista = (dipendente *)malloc(sizeof(dipendente));
        lista->next = NULL;
        strcpy(lista->codiceDipendente,d.codiceDipendente);
        strcpy(lista->nome,d.nome);
        strcpy(lista->cognome,d.cognome);
        strcpy(lista->password,d.password);
        strcpy(lista->dataNascita,d.dataNascita);
        strcpy(lista->telefono,d.telefono);
        return lista;
    }
    // Chiamata ricorsiva
    else{
        lista->next = inserisciDipendenteInCoda(lista->next, d);
    }
    return lista;
}

/* Funzione che stampa lista di utenti
Parametri: lista di utenti
Ritorna:
*/
void stampaListaDipendenti(dipendente *lista){
    // Se lista nulla ritorno
    if(lista == NULL){
        return;
    }
    else{
        // Stampo i campi
        printf("\nNome: %s\n", lista->nome);
        printf("Cognome: %s\n", lista->cognome);
        printf("User ID: %s\n", lista->codiceDipendente);
        printf("Password: %s\n", lista->password);
        printf("Data di Nascita: %s\n", lista->dataNascita);
        printf("Telefono: %s\n", lista->telefono);
        printf("============================================\n");
        // Chiamata ricorsiva
        stampaListaDipendenti(lista->next);
    }
}

/* Funzione che controlla che i dati inseriti siano corretti
Parametro:
Ritorna:
*/
void checkLoginDipendente(){
    system("cls");
    char codiceDipendente[11], password[30];

    printf("\t\t\t---- LOGIN DIPENDENTE ----\n\n");
    // Prendo in input i dati del dipendente
    printf("Inserisci Codice Dipendente: ");
    scanf("%s", codiceDipendente);
    printf("Inserisci Password: ");
    scanf("%s", password);

    // Recupero la lista dei dipendenti da file
    dipendente *listaDipendenti = NULL;
    listaDipendenti = creaListaDipendenti();

    // Verifico la correttezza dei dati inseriti in input
    while(listaDipendenti != NULL){
        if(!strcasecmp(codiceDipendente, listaDipendenti->codiceDipendente)){
            if(!strcmp(password, listaDipendenti->password)){
                printf("\nAccesso effettuato correttamente!\n");
                system("PAUSE");
                menuDipendente(codiceDipendente);
                return;
            }
        }
        listaDipendenti = listaDipendenti->next;
    }

    // Se i dati non sono corretti l'utente può tornare al menù principale o riprovare ad inserire i dati
    printf("Codice Dipendente o Password errati.\n");
    int scelta;
    while(1){
        printf("\n1. Torna al menu' principale.\n2. Riprova.\n");
        printf("Inserisci opzione: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                return;
            case 2:
                checkLoginDipendente();
            default:
                printf("Opzione non valida.\n");
                break;
        }
    }
}
