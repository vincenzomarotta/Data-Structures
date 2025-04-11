#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listFood.h"

/*
Funzione: listFood_listLenght
----------
funzione che restituisce la lunghezza della lista.
----------
Ritorno:
-> 0, se la lista è vuota.
-> numero totale dei nodi presenti nella lista, altrimenti
*/
int listFood_listLenght(FoodList *head)
{
    if (head == NULL)
        return 0;
    else
        return 1 + listFood_listLenght(head->next);
}

/*
Funzione: listFood_isEmpty
----------
funzione che controlla se la lista � vuota.
----------
Ritorno:
-> 1, se la lista e' vuota.
-> 0, altrimenti.
*/
int listFood_isEmpty(FoodList *head)
{
    return (head == NULL);
}

/*
Funzione: listFood_listPrint
----------
Stampa la lista degli alimenti legati ad un driver
----------
Ritorno:
-> nessuno.
*/
void listFood_listPrint(FoodList *head)
{
    if (head == NULL)
        return;
    else
    {
        printf("%d  %s  %d  %d  %s  %lf  %d\n", head->item.barcode, head->item.name, head->item.available, head->item.foodWeight, head->item.brand, head->item.price, head->quantity);
        listFood_listPrint(head->next);
    }
}

/*
Funzione: listFood_freeNode
----------
funzione che dealloca il nodo.
----------
Ritorno:
-> nessuno.
*/

static void _listFood_freeNode(FoodList *head)
{
    free((void *)head);
}

/*
Funzione: listFood_freeList
----------
funzione che dealloca la lista
----------
Ritorno:
-> nessuno.
*/

void listFood_freeList(FoodList **head)
{
    if ((head != NULL) && (*head != NULL))
    {
        listFood_freeList(&((*head)->next));
        _listFood_freeNode(*head);
        return;
    }
    else
        return;
}

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

FoodList *listFood_findPosition(int position, FoodList *head, int cnt)
{
    if (head == NULL)
        return NULL;
    else
    {
        if (position == cnt)
        {
            return head;
        }
        else
        {
            cnt++;
            return listFood_findPosition(position, head->next, cnt);
        }
    }
}

FoodList *listFood_findFoodByPosition(int position, FoodList *head)
{
    if (position >= listFood_listLenght(head))
    {
        return NULL;
    }
    else
    {
        return listFood_findPosition(position, head, 0);
    }
}

/*
Funzione: listFood_insertToFoodListByNode
----------
Inserisce il nodo alla coda della lista.
----------
Ritorno:
-> nessuno.
*/
static void _listFood_insertToFoodListByNode(FoodList **head, FoodList *newNode)
{
    if (head == NULL)
    {
        printf("Errore in insertToFoodListByNode: il puntatore passato era NULL.\n");
        return;
    }
    else
    {
        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            _listFood_insertToFoodListByNode(&((*head)->next), newNode);
        }
    }
}

/*
Funzione: listFood_loadConfirmedFoodListFromDb
----------
funzione che pesca i dati di ogni singolo alimento e chiama la funzione foodList_insertToFoodListByNode
----------
Ritorno:
-> 0, se non viene caricato nulla dal DB.
-> il numero dei nodi inseriti in lista, altrimenti.
*/

int listFood_loadConfirmedFoodListFromDb(FILE *db, FoodList **head) //
{
    if (db == NULL)
    {
        printf("Errore: puntatore/i mancante/i.\n");
        return 0;
    }
    else
    {
        char temp[FOOD_MAX_RECORD_LENGTH];
        char *tempBarcode;
        char *tempName;
        char *tempAvailable;
        char *tempFoodWeight;
        char *tempBrand;
        char *tempPrice;

        if (fgets(temp, FOOD_MAX_RECORD_LENGTH, db) == NULL)
            return 0;
        else
        {
            FoodList *newNode = (FoodList *)calloc(1, sizeof(FoodList));

            if (newNode == NULL)
                return 0 + listFood_loadConfirmedFoodListFromDb(db, head);
            else
            {
                tempBarcode = strtok(temp, ";");
                tempName = strtok(NULL, ";");
                tempAvailable = strtok(NULL, ";");
                tempFoodWeight = strtok(NULL, ";");
                tempBrand = strtok(NULL, ";");
                tempPrice = strtok(NULL, ";");
                newNode->item.barcode = atoi(tempBarcode);
                newNode->item.name = strdup(tempName);
                newNode->item.available = atoi(tempAvailable);
                newNode->item.foodWeight = atoi(tempFoodWeight);
                newNode->item.brand = strdup(tempBrand);
                newNode->item.price = atof(tempPrice);
                _listFood_insertToFoodListByNode(head, newNode);

                return 1 + listFood_loadConfirmedFoodListFromDb(db, head);
            }
        }
    }
}

/*
Funzione: listFood_loadFoodListFromDb
----------
funzione che apre il file FoodList.txt e carica nel sistema applicativo gli alimenti disponibili nei magazzini.
----------
Ritorno:
-> 0, se il file del DB non viene aperto con successo.
-> il numero dei nodi inseriti effettivamente in lista, altrimenti.
*/
int listFood_loadFoodListFromDb(FoodList **head) //
{
    int res;
    FILE *db = fopen("db/foodList.txt", "r");
    if (db == NULL)
    {
        printf("Errore nella lettura del file.\n");
        return 0;
    }
    else
    {
        res = listFood_loadConfirmedFoodListFromDb(db, head);
        fclose(db);
        return res;
    }
}

/*
Funzione: _listFood_removeNode
----------
funzione che dealloca la memoria del nodo rimosso.
----------
Ritorno:
-> 0, se la rimozione NON e' avvenuta.
-> 1, altrimenti.
*/
static int _listFood_removeNode(FoodList *temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    else
    {
        free((void *)temp);
        return 1;
    }
}

/*
Funzione: listFood_removeFoodFromListByBarcode
----------
funzione che ritorna la lista degli alimenti rimuovendo l'elemento, e scrive su file la nuova lista
----------
Ritorno:
-> 0, se la rimozione non ha avuto successo.
-> 1, altrimenti.
*/

int listFood_removeFoodFromListByBarcode(FoodList **head, FoodList *prev, int barcode)
{
    if (head == NULL)
    {
        printf("Errore in checkAvailabilityByFoodBarcode: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        FoodList *temp = NULL;
        if (prev == NULL)
        {
            if ((*head) == NULL) //CASO ELEMENTO NON TROVATO!
            {
                return 0;
            }
            else
            {
                if ((*head)->item.barcode == barcode)
                {
                    temp = (*head);
                    (*head) = (*head)->next;
                    return _listFood_removeNode(temp);
                }
                else
                {
                    prev = (*head);
                    return listFood_removeFoodFromListByBarcode(&((*head)->next), prev, barcode);
                }
            }
        }
        else
        {
            if ((*head) == NULL)
                return 0;
            else
            {
                if ((*head)->item.barcode == barcode)
                {
                    temp = (*head);
                    (*head) = (*head)->next;
                    prev->next = (*head);
                    return _listFood_removeNode(temp);
                }
                else
                {
                    prev = (*head);
                    return listFood_removeFoodFromListByBarcode(&((*head)->next), prev, barcode);
                }
            }
        }
    }
}

/*
Funzione: listFood_addNewFood
----------
funzione che ritorna la lista degli alimenti aggiungendo un nuovo nodo.
----------
Ritorno:
-> 0, se l'inserimento non ha successo e/o rimozione non ha successo.
-> 1, altrimenti.
*/
int listFood_addNewFood(FoodList **head, int barcode, char *name, int available, int foodWeight, char *brand, double price)
{
    if (head == NULL)
    {
        printf("Errore in checkAvailabilityByFoodBarcode: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        FoodList *newNode = (FoodList *)calloc(1, sizeof(FoodList));
        newNode->item.barcode = barcode;
        strcpy(newNode->item.name, name);
        newNode->item.available = available;
        newNode->item.foodWeight = foodWeight;
        strcpy(newNode->item.brand, brand);
        newNode->item.price = price;
        _listFood_insertToFoodListByNode(head, newNode);
        return 1;
    }
}

/*
Funzione: listFood_writeOnDbFoodListWithoutFoodByBarcode
----------
funzione che modifica il file DB di FoodList con rimozione del Food scelto.
----------
Ritorno:
-> 0, se la scrittura non va a buon fine.
-> 1, altrimenti.
*/
int listFood_writeOnDbFoodListWithoutFoodByBarcode(FoodList **head, int barcode) //
{
    int res = listFood_removeFoodFromListByBarcode(head, NULL, barcode);

    FoodList *temp = (*head);

    FILE *fpOut = fopen("db/foodList.txt", "w");

    if (fpOut == NULL)
        return 0;
    else
    {
        while (temp != NULL)
        {
            fprintf(fpOut, "%d;%s;%d;%d;%s;%lf\n", temp->item.barcode, temp->item.name, temp->item.available, temp->item.foodWeight, temp->item.brand, temp->item.price);
            temp = temp->next;
        }
        return res;
    }
}

/*
Funzione: listFood_checkAvailabilityByFoodBarcode
----------
funzione che ritorna la disponibilita' in magazzino di uno specifico alimento.
----------
Ritorno:
-> 0, se non c'e' abbastanza disponibilita'
-> 1, se c'e' abbastanza disponibilita' e modifica con successo quella presente
*/
int listFood_checkAvailabilityByFoodBarcode(FoodList **head, int barcode, int quantityTaken) //CASO DI RICERCA DELLA DISPONIBILITA' IN LISTA
{
    if (head == NULL)
    {
        printf("Errore in checkAvailabilityByFoodBarcode: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        if (*head == NULL)
            return 0;
        else
        {
            if ((*head)->item.barcode == barcode)
                return listFood_updateAvailability((*head), quantityTaken, NULL);
            else
                return listFood_checkAvailabilityByFoodBarcode(&((*head)->next), barcode, quantityTaken);
        }
    }
}

/*
Funzione: listFood_updateDbFoodListBeforeCloseSystem
----------
funzione che scrive sul file la lista aggiornata.
----------
Ritorno:
-> 0, se non avviene la scrittura
-> 1, se avviene la scrittura
*/
int listFood_updateDbFoodListBeforeCloseSystem(FoodList **head)
{
    FILE *fpOut = fopen("db/foodList.txt", "w");
    if (fpOut == NULL)
        return 0;

    FoodList *temp = *head;

    while (temp != NULL)
    {
        fprintf(fpOut, "%d;%s;%d;%d;%s;%lf\n", temp->item.barcode, temp->item.name, temp->item.available, temp->item.foodWeight, temp->item.brand, temp->item.price);
        temp = temp->next;
    }
    fclose(fpOut);
    return 1;
}

/*
Funzione: listFood_findFoodByBarcode
----------
funzione che cerca il nodo da copiare in NewNodo nell'inserimento di un alimento nella vettura del driver
----------
Ritorno:
-> nodo, se trova l'alimento con quel barcode;
-> NULL, se non trova nessun alimento con quel barcode;
*/

FoodList *listFood_findFoodByBarcode(FoodList *head, int barcode)
{
    if (head != NULL)
        return (head->item.barcode == barcode) ? head : listFood_findFoodByBarcode(head->next, barcode);
    else
        return NULL;
}

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

/*
Funzione: listFood_calculateTotalWeight
----------
funzione che calcola il peso totale della lista di tutti gli alimenti trasportati dal driver.
----------
Ritorno:
-> 0, se non ha alimenti nella vettura.
-> totale del peso di tutti gli alimenti.
*/

int listFood_calculateTotalWeight(FoodList *items)
{
    if (items == NULL)
    {
        return 0;
    }
    else
    {
        return ((items->quantity) * (items->item.foodWeight)) + listFood_calculateTotalWeight(items->next);
    }
}

/*
Funzione: listFood_insertToListItemsForDriver
----------
funzione che inserisce un nuovo alimento nella lista degli alimenti trasportarti dal driver
----------
Ritorno:
-> 0, se non avviene l'inserimento;
-> 1, altrimenti.
*/

FoodList *listFood_insertToListItemsForDriver(FoodList *items, int quantityTaken, FoodList *cpyNodo)
{
    if (cpyNodo == NULL) //Caso in cui non e' stato trovato nessun nodo da listFood_findFoodByPosition
    {
        printf("cpyNodo e' NULL!\n");
        return NULL;
    }
    else
    {
        {
            if (items == NULL)
            {
                items = (FoodList *)calloc(1, sizeof(FoodList));
                if (items == NULL)
                {
                    printf("Errore in insertToListItemsForDriver: impossibile allocare nuovo items");
                    return NULL;
                }

                items->item.name = (char *)calloc(FOOD_MAX_NAME_LENGTH, sizeof(char));
                if (items->item.name == NULL)
                {
                    printf("Errore in insertToListItemsForDriver: impossibile allocare nuovo item.name");
                    return NULL;
                }

                items->item.brand = (char *)calloc(FOOD_MAX_BRAND_LENGTH, sizeof(char));
                if (items->item.brand == NULL)
                {
                    printf("Errore in insertToListItemsForDriver: impossibile allocare nuovo item.brand");
                    return NULL;
                }

                items->item.barcode = cpyNodo->item.barcode;
                strcpy(items->item.name, cpyNodo->item.name);
                items->item.available = cpyNodo->item.available;
                items->item.foodWeight = cpyNodo->item.foodWeight;
                strcpy(items->item.brand, cpyNodo->item.brand);
                items->item.price = cpyNodo->item.price;
                items->quantity = quantityTaken;
            }
            else
            {
                items->next = listFood_insertToListItemsForDriver(items->next, quantityTaken, cpyNodo);
            }
        }
    }

    return items;
}

/*
Funzione: listFood_checkAvailability
----------
funzione che controlla la disponibilita' del prodotto in magazzino
----------
Ritorno:
-> 0, se non c'e' disponibilita
-> 1, altrimenti.
*/

int listFood_checkAvailability(int foodQta, FoodList *nodo)
{
    if (nodo == NULL)
        return 0;
    else
    {
        if (foodQta > nodo->item.available)
            return 0;
        else
            return nodo->item.available;
    }
}

/*
Funzione: listFood_updateAvailability
----------
funzione che modifica la disponibilita' del campo available se la quantita' presa dal driver e' maggiore o uguale a quella rimanente nel magazzino
----------
Ritorno:
-> 0, se non modifica la disponibilita'
-> 1, se modifica la disponibilita'
*/
int listFood_updateAvailability(FoodList *node, int quantityTaken, FoodList *head) //CASO CHE PASSIAMO NODO SPECIFICO
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        if (!strcasecmp(head->item.name, node->item.name) && head->item.barcode == node->item.barcode)
        {
            head->item.available -= quantityTaken;
            return 1;
        }
        else
        {
            return listFood_updateAvailability(node, quantityTaken, head->next);
        }
    }
}

/*
Funzione: listFood_calculateTotalPrice
----------
funzione che calcola il prezzo totale della lista di tutti gli alimenti trasportati dal driver.
----------
Ritorno:
-> 0, se non ha alimenti nella vettura.
-> totale del prezzo di tutti gli alimenti.
*/
double listFood_calculateTotalPrice(FoodList *items)
{
    if (items == NULL)
    {
        return 0;
    }
    else
    {
        return ((items->quantity) * (items->item.price)) + listFood_calculateTotalPrice(items->next);
    }
}