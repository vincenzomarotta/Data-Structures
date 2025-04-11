#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "driver.h"
#include "listFood.h"

/*************************/
/* Funzioni sulla lista  */
/*************************/

/*
Funzione: driver_newDriver
----------
Crea una nuova struttura driver.
----------
Ritorno:
-> Puntatore ad un a struttura driver in caso di successo.
-> NULL altrimenti.
*/
Driver *driver_newDriver()
{
    Driver *d = (Driver *)malloc(sizeof(Driver));

    if (d == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione username
    d->username = (char *)calloc(DRIVER_MAX_USERNAME_LENGTH, sizeof(char));
    if (d->username == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione password
    d->password = (char *)calloc(DRIVER_MAX_PASSWORD_LENGTH, sizeof(char));
    if (d->password == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione cf
    d->cf = (char *)calloc(DRIVER_MAX_CF_LENGTH, sizeof(char));
    if (d->cf == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione nome
    d->name = (char *)calloc(DRIVER_MAX_NAME_SURNAME_LENGTH, sizeof(char));
    if (d->name == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione cognome
    d->surname = (char *)calloc(DRIVER_MAX_NAME_SURNAME_LENGTH, sizeof(char));
    if (d->surname == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione email
    d->email = (char *)calloc(DRIVER_MAX_EMAIL_LENGTH, sizeof(char));
    if (d->email == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione numero di telefono
    d->telephone = (char *)calloc(DRIVER_MAX_TELEPHONE_LENGTH, sizeof(char));
    if (d->telephone == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione indirizzo
    d->address = (char *)calloc(DRIVER_MAX_ADDRESS_LENGTH, sizeof(char));
    if (d->address == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione nome veicolo
    d->vehicleName = (char *)calloc(DRIVER_MAX_VEHICLENAME_LENGTH, sizeof(char));
    if (d->vehicleName == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    // allocazione targa
    d->plate = (char *)calloc(DRIVER_MAX_PLATE_LENGTH, sizeof(char));
    if (d->plate == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }

    d->items = (FoodList *)malloc(sizeof(FoodList));
    if (d->items == NULL)
    {
        printf("Errore in newDriver: impossibile allocare nuovo driver");
        return NULL;
    }
    else
        d->items = NULL;

    return d;
}

/*
Funzione: driver_append
----------
Inserisce un nuovo driver in coda alla lista.
----------
Ritorno:
-> lista di driver
*/
Driver *driver_append(Driver *list, Driver *newDriver)
{
    if (list == NULL)
    {
        list = driver_newDriver();
        // Copio i campi
        list->username = strdup(newDriver->username);
        list->password = strdup(newDriver->password);
        list->cf = strdup(newDriver->cf);
        list->name = strdup(newDriver->name);
        list->surname = strdup(newDriver->surname);
        list->email = strdup(newDriver->email);
        list->telephone = strdup(newDriver->telephone);
        list->address = strdup(newDriver->address);
        list->vehicleWeight = newDriver->vehicleWeight;
        list->vehicleName = strdup(newDriver->vehicleName);
        list->plate = strdup(newDriver->plate);

        list->next = NULL;

        return list;
    }
    else
    {
        // chiamata ricorsiva
        list->next = driver_append(list->next, newDriver);
    }
    return list;
}

/*
Funzione: driver_createList
----------
Funzione per creare una lista di driver utilizzando il file.
----------
Ritorno:
-> lista di driver
*/
Driver *driver_createList()
{
    Driver *listaDriver = NULL;
    FILE *db;

    // apertura del file
    db = fopen(FILE_LOGIN_DRIVER, "r");

    if (db == NULL)
    {
        printf("Errore: apertura del file non riuscita.\n");
        return listaDriver;
    }

    // riga per i dati
    char temp[DRIVER_MAX_RECORD_LENGTH];

    while (fgets(temp, DRIVER_MAX_RECORD_LENGTH, db) != NULL)
    {
        // driver temporaneo per recuperare i valori
        Driver *tmpDriver = driver_newDriver();
        // recupero i valori
        tmpDriver->username = strtok(temp, ";");
        tmpDriver->password = strtok(NULL, ";");
        tmpDriver->cf = strtok(NULL, ";");
        tmpDriver->name = strtok(NULL, ";");
        tmpDriver->surname = strtok(NULL, ";");
        tmpDriver->email = strtok(NULL, ";");
        tmpDriver->telephone = strtok(NULL, ";");
        tmpDriver->address = strtok(NULL, ";");
        tmpDriver->vehicleWeight = atoi(strtok(NULL, ";"));
        tmpDriver->vehicleName = strtok(NULL, ";");
        tmpDriver->plate = strtok(NULL, ";");

        // inserimento in lista
        listaDriver = driver_append(listaDriver, tmpDriver);
        free(tmpDriver);
    }

    fclose(db);
    return listaDriver;
}

/*
Funzione: driver_printDriverList
----------
Stampa la lista di driver.
----------
Ritorno:
-> 1 se la stampa avviene con successo.
-> 0 altrimenti.
*/
int driver_printDriverList(Driver *list)
{
    if (list == NULL)
        return 0;
    while (list != NULL)
    {
        printf("Username: %s\n", list->username);
        printf("Password: %s\n", list->password);
        printf("Codice Fiscale: %s\n", list->cf);
        printf("Nome: %s\n", list->name);
        printf("Cognome: %s\n", list->surname);
        printf("Email: %s\n", list->email);
        printf("Telefono: %s\n", list->telephone);
        printf("Indirizzo: %s\n", list->address);
        printf("Nome Veicolo associato: %s\n", list->vehicleName);
        printf("Targa: %s\n", list->plate);
        printf("Peso del Veicolo: %d\n", list->vehicleWeight);
        printf("--------------------------------------------\n");
        list = list->next;
    }

    return 1;
}

/*
Funzione: driver_deleteDriverByUsername
----------
Cancella un driver dal file utilizzando l'username.
----------
Ritorno:
-> 1 se eliminazione avviene con successo
-> 0 altrimenti
*/
int driver_deleteDriverByUsername(char *username)
{
    Driver *driverList = driver_createList();
    Driver *tmp = driverList;
    Driver *prev = NULL;

    if (driverList == NULL)
        return 0;

    // controllo se devo eliminare in testa
    if (!strcasecmp(tmp->username, username))
    {
        driverList = driverList->next;
        free(tmp);
    }
    else
    {
        // scorro la lista finchè non trovo nodo da eliminare
        while (tmp != NULL && strcasecmp(tmp->username, username))
        {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp != NULL)
        {
            prev->next = tmp->next;
            free(tmp);
        }
    }

    // riscrivo nel file la lista aggiornata di driver
    FILE *db;
    db = fopen(FILE_LOGIN_DRIVER, "w");

    if (db == NULL)
    {
        printf("Errore durante l'apertura del file, riprova.\n");
        return 0;
    }

    while (driverList != NULL)
    {
        fprintf(db, "%s;%s;%s;%s;%s;%s;%s;%s;%d;%s;%s;\n", driverList->username, driverList->password, driverList->cf, driverList->name, driverList->surname, driverList->email,
                driverList->telephone, driverList->address, driverList->vehicleWeight, driverList->vehicleName, driverList->plate);
        driverList = driverList->next;
    }

    fclose(db);
    return 1;
}

/**************************/
/* Funzioni registrazione */
/**************************/

/*
Funzione: driver_initializeDriver
----------
Funzione per creare un nuovo driver controllando la correttezza dei campi inseriti.
----------
Ritorno:
-> puntatore a driver
*/
Driver *driver_initializeDriver()
{
    Driver *d = driver_newDriver();

    if (d == NULL)
    {
        printf("Errore: allocazione nuovo driver non riuscita.\n");
        return NULL;
    }

    fflush(stdin);
    printf("Inserisci username (MAX %d CARATTERI): ", DRIVER_MAX_USERNAME_LENGTH - 1);
    scanf("%s", d->username);

    while (strlen(d->username) > DRIVER_MAX_USERNAME_LENGTH || driver_checkUsernameExistence(d->username))
    {
        printf("Username errato o gia' presente, riprova: ");
        scanf("%s", d->username);
    }

    fflush(stdin);
    printf("Inserisci password (MAX %d CARATTERI): ", DRIVER_MAX_PASSWORD_LENGTH - 1);
    scanf("%s", d->password);

    while (strlen(d->password) > DRIVER_MAX_PASSWORD_LENGTH || !strcasecmp(d->password, d->username))
    {
        printf("Formato password errato, riprova: ");
        scanf("%s", d->password);
    }

    fflush(stdin);
    printf("Inserisci Codice Fiscale (16 CARATTERI): ");
    scanf("%s", d->cf);

    while (strlen(d->cf) != DRIVER_MAX_CF_LENGTH || driver_checkCfExistence(d->cf))
    {
        printf("Formato codice fiscale errato, riprova: ");
        scanf("%s", d->cf);
    }

    for (int i = 0; i < strlen(d->cf); i++)
    {
        d->cf[i] = toupper(d->cf[i]);
    }

    fflush(stdin);
    printf("Inserisci nome (MAX %d CARATTERI): ", DRIVER_MAX_NAME_SURNAME_LENGTH - 1);
    scanf("%s", d->name);

    while (strlen(d->name) > DRIVER_MAX_NAME_SURNAME_LENGTH || !driver_isAllAlpha(d->name, strlen(d->name)))
    {
        printf("Formato nome errato, riprova: ");
        scanf("%s", d->name);
    }

    fflush(stdin);
    printf("Inserisci cognome (MAX %d CARATTERI): ", DRIVER_MAX_NAME_SURNAME_LENGTH - 1);
    scanf("%s", d->surname);

    while (strlen(d->surname) > DRIVER_MAX_NAME_SURNAME_LENGTH || !driver_isAllAlpha(d->surname, strlen(d->surname)))
    {
        printf("Formato cognome errato, riprova: ");
        scanf("%s", d->surname);
    }

    fflush(stdin);
    printf("Inserisci email (MAX %d CARATTERI): ", DRIVER_MAX_EMAIL_LENGTH - 1);
    scanf("%s", d->email);

    while (strlen(d->email) > DRIVER_MAX_EMAIL_LENGTH || driver_checkEmailExistence(d->email))
    {
        printf("Formato email errato, riprova: ");
        scanf("%s", d->email);
    }

    fflush(stdin);
    printf("Inserisci numero di telefono (MAX %d CARATTERI): ", DRIVER_MAX_TELEPHONE_LENGTH - 1);
    scanf("%s", d->telephone);

    while (strlen(d->telephone) > DRIVER_MAX_TELEPHONE_LENGTH || !driver_isAllDigit(d->telephone, strlen(d->telephone)))
    {
        printf("Formato numero di telefono errato, riprova: ");
        scanf("%s", d->telephone);
    }

    fflush(stdin);
    printf("Inserisci indirizzo (MAX %d CARATTERI): ", DRIVER_MAX_ADDRESS_LENGTH - 1);
    gets(d->address);

    while (strlen(d->address) > DRIVER_MAX_ADDRESS_LENGTH)
    {
        printf("Formato indirizzo errato, riprova: ");
        gets(d->address);
    }

    fflush(stdin);
    printf("Inserisci nome del tuo veicolo (MAX %d CARATTERI): ", DRIVER_MAX_VEHICLENAME_LENGTH - 1);
    gets(d->vehicleName);

    while (strlen(d->vehicleName) > DRIVER_MAX_VEHICLENAME_LENGTH)
    {
        printf("Formato nome veicolo errato, riprova: ");
        gets(d->vehicleName);
    }

    fflush(stdin);
    printf("Inserisci la targa del tuo veicolo (MAX %d CARATTERI): ", DRIVER_MAX_PLATE_LENGTH - 1);
    scanf("%s", d->plate);

    while (strlen(d->plate) > DRIVER_MAX_PLATE_LENGTH)
    {
        printf("Formato targa errato, riprova: ");
        gets(d->plate);
    }

    fflush(stdin);
    printf("Inserisci il peso del tuoi veicolo: ");
    scanf("%d", &d->vehicleWeight);

    while (d->vehicleWeight <= 0)
    {
        printf("Formato peso non valido, riprova: ");
        scanf("%d", &d->vehicleWeight);
    }

    return d;
}

/*
Funzione: driver_checkUsernameExistence
----------
Funzione che controlla se un username è gia presente nel file.
----------
Ritorno:
-> 0 se l'username non è presente
-> 1 altrimenti
*/
int driver_checkUsernameExistence(char *username)
{
    Driver *listaDriver = driver_createList();
    if (listaDriver == NULL)
    {
        return 0;
    }
    while (listaDriver != NULL)
    {
        if (!strcasecmp(listaDriver->username, username))
        {
            return 1;
        }
        listaDriver = listaDriver->next;
    }

    free(listaDriver);
    return 0;
}

/*
Funzione: driver_checkEmailExistence
----------
Funzione che controlla se un email è gia presente nel file.
----------
Ritorno:
-> 0 se l'email non è presente
-> 1 altrimenti
*/
int driver_checkEmailExistence(char *email)
{
    Driver *listaDriver = driver_createList();
    if (listaDriver == NULL)
    {
        return 0;
    }
    while (listaDriver != NULL)
    {
        if (!strcasecmp(listaDriver->email, email))
        {
            return 1;
        }
        listaDriver = listaDriver->next;
    }

    free(listaDriver);
    return 0;
}

/*
Funzione: driver_checkCfExistence
----------
Funzione che controlla se un codice fiscale è gia presente nel file.
----------
Ritorno:
-> 0 se il codice fiscale non è presente
-> 1 altrimenti
*/
int driver_checkCfExistence(char *cf)
{
    Driver *listaDriver = driver_createList();
    if (listaDriver == NULL)
    {
        return 0;
    }
    while (listaDriver != NULL)
    {
        if (!strcasecmp(listaDriver->cf, cf))
        {
            return 1;
        }
        listaDriver = listaDriver->next;
    }

    free(listaDriver);
    return 0;
}

/*
Funzione: driver_isAllAlpha
----------
Funzione che controlla che una stringa sia composta da soli caratteri.
----------
Ritorno:
-> 1 se ci sono solo caratteri
-> 0 altrimenti
*/
int driver_isAllAlpha(char *string, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (isdigit(string[i]))
        {
            return 0;
        }
    }
    return 1;
}

/*
Funzione: driver_isAllDigit
----------
Funzione che controlla che una stringa sia composta da soli numeri.
----------
Ritorno:
-> 1 se ci sono solo numeri
-> 0 altrimenti
*/
int driver_isAllDigit(char *string, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(string[i]))
        {
            return 0;
        }
    }
    return 1;
}

/*
Funzione: driver_checkUsername
----------
Funzione che controlla la correttezza dell'username.
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkUsername(char *username)
{
    if (strlen(username) < DRIVER_MIN_FIELD_LENGTH || strlen(username) > DRIVER_MAX_USERNAME_LENGTH || driver_checkUsernameExistence(username))
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkPassword
----------
Funzione che controlla la correttezza della password.
----------
Ritorno:
-> 1 se è corretta
-> 0 altrimenti
*/
int driver_checkPassword(char *password)
{
    if (strlen(password) < DRIVER_MIN_FIELD_LENGTH || strlen(password) == 0 || strlen(password) > DRIVER_MAX_PASSWORD_LENGTH)
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkCf
----------
Funzione che controlla la correttezza del codice fiscale.
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkCf(char *cf)
{
    if (strlen(cf) != DRIVER_MAX_CF_LENGTH - 1 || driver_checkCfExistence(cf))
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkName
----------
Funzione che controlla la correttezza del nome (o del cognome).
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkName(char *name)
{
    if (strlen(name) < DRIVER_MIN_NAME_SURNAME_LENGTH || strlen(name) > DRIVER_MAX_NAME_SURNAME_LENGTH || !driver_isAllAlpha(name, strlen(name)))
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkEmail
----------
Funzione che controlla la correttezza dell'email.
----------
Ritorno:
-> 1 se è corretta
-> 0 altrimenti
*/
int driver_checkEmail(char *email)
{
    if (strlen(email) < DRIVER_MIN_FIELD_LENGTH || strlen(email) > DRIVER_MAX_EMAIL_LENGTH || driver_checkEmailExistence(email))
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkTelephone
----------
Funzione che controlla la correttezza del numero di telefono.
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkTelephone(char *telephone)
{
    if (strlen(telephone) < DRIVER_MIN_FIELD_LENGTH || strlen(telephone) > DRIVER_MAX_TELEPHONE_LENGTH || !driver_isAllDigit(telephone, strlen(telephone)))
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkAddress
----------
Funzione che controlla la correttezza dell'indirizzo.
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkAddress(char *address)
{
    if (strlen(address) < DRIVER_MIN_FIELD_LENGTH || strlen(address) > DRIVER_MAX_ADDRESS_LENGTH)
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkVehicleName
----------
Funzione che controlla la correttezza del nome dei veicolo.
----------
Ritorno:
-> 1 se è corretto
-> 0 altrimenti
*/
int driver_checkVehicleName(char *vehicleName)
{
    if (strlen(vehicleName) < DRIVER_MIN_FIELD_LENGTH || strlen(vehicleName) > DRIVER_MAX_VEHICLENAME_LENGTH)
        return 0;
    else
        return 1;
}

/*
Funzione: driver_checkPlate
----------
Funzione che controlla la correttezza della targa.
----------
Ritorno:
-> 1 se è corretta
-> 0 altrimenti
*/
int driver_checkPlate(char *plate)
{
    if (strlen(plate) < DRIVER_MIN_FIELD_LENGTH || strlen(plate) > DRIVER_MAX_PLATE_LENGTH)
        return 0;
    else
        return 1;
}

/*
Funzione: driver_registration
----------
Funzione che registra un nuovo driver.
----------
Ritorno:
-> 1 se la registrazione avviene con successo
-> 0 altrimenti
*/
int driver_registration(Driver *newDriver)
{
    if (newDriver == NULL)
    {
        return 0;
    }

    // apertura file in append
    FILE *db;
    db = fopen(FILE_LOGIN_DRIVER, "a");

    if (db == NULL)
    {
        db = fopen(FILE_LOGIN_DRIVER, "w");
        if (db == NULL)
            return 0;
    }

    fprintf(db, "%s;%s;%s;%s;%s;%s;%s;%s;%d;%s;%s;\n", newDriver->username, newDriver->password, newDriver->cf, newDriver->name, newDriver->surname, newDriver->email,
            newDriver->telephone, newDriver->address, newDriver->vehicleWeight, newDriver->vehicleName, newDriver->plate);

    fclose(db);
    return 1;
}

/*******************/
/* Funzioni login */
/*****************/

/*
Funzione: driver_login
----------
Funzione che controlla che il login del driver venga effettuato correttamente.
----------
Ritorno:
-> 1 se il login avviene con successo
-> 0 altrimenti
*/
int driver_login(char *username, char *password, Driver **driver)
{
    Driver *driverList = driver_createList();

    // controllo la correttezza di username e password
    while (driverList != NULL)
    {
        if (!strcasecmp(driverList->username, username))
        {
            if (!strcmp(driverList->password, password))
            {
                *driver = driverList;
                return 1;
            }
        }
        driverList = driverList->next;
    }

    *driver = NULL;
    return 0;
}

/*********************/
/* Funzioni storico */
/*******************/

/*
Funzione: driver_printfDeliveryHistory
----------
Funzione che scrive sul file la consegna.
----------
Ritorno:
-> 1 se la scrittura avviene con successo
-> 0 altrimenti
*/
int driver_printDeliveryHistory(Driver *d, int startIsland, int destinationIsland, double totalPrice)
{
    FILE *db;

    db = fopen(FILE_ORDER_HISTORY, "a");

    if (db == NULL)
    {
        db = fopen(FILE_ORDER_HISTORY, "w");
        if (db == NULL)
        {
            return 0;
        }
    }

    // Prendo l'orario della consegna
    time_t rawTime1 = time(NULL);
    struct tm *tt = (struct tm *)malloc(sizeof(struct tm));
    char dateBuffer[20];
    localtime_s(tt, &rawTime1);
    strftime(dateBuffer, 20, "%x %X", tt);

    // Stampa delle informazioni generali della consegna
    fprintf(db, "%s;%s;%s;Island %d;Island %d;%.2lf;%s;", d->username, d->name, d->surname, startIsland, destinationIsland, totalPrice, dateBuffer);

    // Stampa del nome degli alimenti con relativa quantità consegnata
    while (d->items != NULL)
    {
        fprintf(db, "%s;%d;", d->items->item.name, d->items->quantity);
        d->items = d->items->next;
    }

    fprintf(db, "\n");

    fclose(db);

    return 1;
}

/*

Funzione: driver_printDeliveryHistoryByUsername

----------

Funzione che stampa lo storico delle consegne di un driver.

----------

Ritorno:

-> 1 se la stampa avviene con successo

-> 0 altrimenti

*/

int driver_printDeliveryHistoryByUsername(char *username)
{
    FILE *db;

    db = fopen(FILE_ORDER_HISTORY, "r");
    if (db == NULL)
    {
        return 0;
    }

    char temp[DRIVER_MAX_RECORD_LENGTH];
    char *token;
    char *user;
    char *startIsland;
    char *destinationIsland;
    char *totalPrice;
    char *date;

    while (fgets(temp, DRIVER_MAX_RECORD_LENGTH, db) != NULL)
    {
        // recupero i valori

        user = strtok(temp, ";");
        if (!strcasecmp(username, user))
        {
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            startIsland = strtok(NULL, ";");
            destinationIsland = strtok(NULL, ";");
            totalPrice = strtok(NULL, ";");
            date = strtok(NULL, ";");
            printf("Data: %s\n", date);
            printf("Isola di Partenza: %s\n", startIsland);
            printf("Isola di Destinazione: %s\n", destinationIsland);
            printf("Prezzo Totale: %s\n\n", totalPrice);
        }
    }

    fclose(db);
    return 1;
}