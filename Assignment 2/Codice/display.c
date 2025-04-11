#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "display.h"
#include "driver.h"
#include "graph.h"
#include "listFood.h"

/*
Funzione: _gotoXY
----------
Facilita la gestione degli spostamenti del cursore.
----------
Ritorno: nessuno.
*/
static void _gotoXY(HANDLE hconsole, COORD cursorPosition, int x, int y)
{
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(hconsole, cursorPosition);
}

static void _clearBuffer(void)
{
    char c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int display_mainMenu(HANDLE hconsole)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;
    int menuItem = 0, x = 7;
    int running = 1;
    char c;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Piattaforma I-eats");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("------------------");
    _gotoXY(hconsole, cursorPosition, 0, 2);
    printf("Usa le frecce direzionali per muoverti.");
    _gotoXY(hconsole, cursorPosition, 0, 5);
    printf("Scegli cosa vuoi fare:");
    _gotoXY(hconsole, cursorPosition, 10, 7);
    printf("Login");
    _gotoXY(hconsole, cursorPosition, 10, 8);
    printf("Registrazione nuovo driver");
    _gotoXY(hconsole, cursorPosition, 10, 9);
    printf("Mappa");
    _gotoXY(hconsole, cursorPosition, 10, 10);
    printf("Esci");
    _gotoXY(hconsole, cursorPosition, 8, 7);
    printf("->");

    while (running)
    {
        c = 0;

        switch (c = getch())
        {
        case KEY_DOWN:
            if (x != 10)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x++;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem++;
            }
            break;

        case KEY_UP:
            if (x != 7)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x--;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem--;
            }
            break;

        case KEY_ENTER:
            running = 0;
            break;
        }
    }

    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    switch (menuItem)
    {
    case 0:
        return 10;

    case 1:
        return 50;

    case 2:
        return 60;

    case 3:
        return 10000;

    default:
        return 0;
    }
}

int display_driverLogin(HANDLE hconsole, Driver **driver)
{
    COORD cursorPosition;
    char username[50]; //DA AGGIUSTARE
    char password[50];

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Login Driver");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-------------");
    _gotoXY(hconsole, cursorPosition, 0, 2);
    printf("Inserisci username e password per effettuare l'accesso.");

    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Username: ");
    scanf(" %[^\n]s", username);
    _clearBuffer();
    _gotoXY(hconsole, cursorPosition, 0, 5);
    printf("Password: ");
    scanf(" %[^\n]s", password);
    _clearBuffer();

    if (!driver_login(username, password, driver))
    {
        _gotoXY(hconsole, cursorPosition, 0, 7);
        printf("ATTENZIONE: username e/o password non validi.");
        Sleep(3000);
        return 0;
    }
    else
        return 20;
}

int display_driverMenu(HANDLE hconsole, Driver *driver)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;
    int menuItem = 0, x = 6;
    int running = 1;
    char c;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Salve %s %s", driver->name, driver->surname);
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("----------------");

    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Cosa vuoi fare?");
    _gotoXY(hconsole, cursorPosition, 10, 6);
    printf("Programma consegna");
    _gotoXY(hconsole, cursorPosition, 10, 7);
    printf("Storico consegne");
    _gotoXY(hconsole, cursorPosition, 10, 8);
    printf("Informazioni sull'account");
    _gotoXY(hconsole, cursorPosition, 10, 9);
    printf("Cancella account");
    _gotoXY(hconsole, cursorPosition, 10, 10);
    printf("Ritorna al menu principale");
    _gotoXY(hconsole, cursorPosition, 8, 6);
    printf("->");

    while (running)
    {
        c = 0;

        switch (c = getch())
        {
        case KEY_DOWN:
            if (x != 10)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x++;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem++;
            }
            break;

        case KEY_UP:
            if (x != 6)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x--;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem--;
            }
            break;

        case KEY_ENTER:
            running = 0;
            break;
        }
    }

    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    switch (menuItem)
    {
    case 0:
        return 30;

    case 1:
        return 35;

    case 2:
        return 37;

    case 3:
        return 40;

    case 4:
        return 0;

    default:
        return 0;
    }
}

int display_driverDeliveryProgram(HANDLE hconsole, Driver *driver, AdjacencyGraph *graph, FoodList *foodList)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;
    int menuItem = 0, x = 6;
    int running = 1;
    char c;

    int listIndex = 6;
    unsigned arrayIndex[graph->numberOfNodes];
    unsigned startIslandPosition;
    unsigned destinationIslandPosition;

    FoodList *temp = NULL;
    int foodQta = 0;
    int foodQtaArray[listFood_listLenght(foodList)];

    for (int i = 0; i < listFood_listLenght(foodList); i++)
        foodQtaArray[i] = 0;

    /* Isola di partenza */

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Programmazione consegna");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-----------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Scegli isola di partenza:");
    for (int i = 0; i < graph->arrayLength; i++)
    {
        if ((graph->nodeArray[i]) && (!graph->nodeArray[i]->isDisabled))
        {
            _gotoXY(hconsole, cursorPosition, 10, listIndex);
            printf("%d) %s", listIndex - 5, graph->nodeArray[i]->name);
            arrayIndex[listIndex - 6] = i;
            listIndex++;
        }
    }
    _gotoXY(hconsole, cursorPosition, 8, 6);
    printf("->");

    while (running)
    {
        c = 0;

        switch (c = getch())
        {
        case KEY_DOWN:
            if (x != (graph->numberOfNodes + 5))
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x++;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem++;
            }
            break;

        case KEY_UP:
            if (x != 6)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x--;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem--;
            }
            break;

        case KEY_ENTER:
            running = 0;
            break;
        }
    }
    startIslandPosition = arrayIndex[menuItem];

    /* Isola di destinazione */

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Programmazione consegna");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-----------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Scegli isola di destinazione:");
    listIndex = 6;
    for (int i = 0; i < graph->arrayLength; i++)
    {
        if ((graph->nodeArray[i]) && (!graph->nodeArray[i]->isDisabled))
        {
            _gotoXY(hconsole, cursorPosition, 10, listIndex);
            printf("%d) %s", listIndex - 5, graph->nodeArray[i]->name);
            arrayIndex[listIndex - 6] = i;
            listIndex++;
        }
    }
    _gotoXY(hconsole, cursorPosition, 8, 6);
    printf("->");

    menuItem = 0;
    x = 6;
    running = 1;
    while (running)
    {
        c = 0;

        switch (c = getch())
        {
        case KEY_DOWN:
            if (x != (graph->numberOfNodes + 5))
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x++;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem++;
            }
            break;

        case KEY_UP:
            if (x != 6)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x--;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem--;
            }
            break;

        case KEY_ENTER:
            running = 0;
            break;
        }
    }
    destinationIslandPosition = arrayIndex[menuItem];

    /* Scelta cibo */

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Programmazione consegna");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-----------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Cibario:");
     _gotoXY(hconsole, cursorPosition, 41, 6);
    printf("Qta' | Peso unita'");

    temp = foodList;
    listIndex = 8;
    while (temp)
    {
        _gotoXY(hconsole, cursorPosition, 10, listIndex);
        printf("%d) %s", listIndex - 7, temp->item.name);
        _gotoXY(hconsole, cursorPosition, 41, listIndex);
        printf("%d", temp->item.available);
        _gotoXY(hconsole, cursorPosition, 50, listIndex);
        printf("%d", temp->item.foodWeight);

        listIndex++;
        temp = temp->next;
    }
    _gotoXY(hconsole, cursorPosition, 10, listIndex);
    printf("%d) Completa", listIndex - 7);
    _gotoXY(hconsole, cursorPosition, 10, listIndex + 1);
    listIndex++;
    printf("%d) Annulla", listIndex - 7);
    _gotoXY(hconsole, cursorPosition, 8, 8);
    printf("->");

    menuItem = 0;
    x = 8;
    running = 1;
    while (running)
    {
        c = 0;

        switch (c = getch())
        {
        case KEY_DOWN:
            if (x != listIndex)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x++;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem++;
            }
            break;

        case KEY_UP:
            if (x != 8)
            {
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("  ");
                x--;
                _gotoXY(hconsole, cursorPosition, 8, x);
                printf("->");
                menuItem--;
            }
            break;

        case KEY_ENTER:
            if (menuItem == listFood_listLenght(foodList))
            {
                int ctrl = 0;

                running = 0;
                for (int i = 0; i < listFood_listLenght(foodList); i++)
                    if (foodQtaArray[i])
                    {
                        ctrl = 1;
                        break;
                    }

                if (ctrl)
                    running = 0;
                else
                {
                    _gotoXY(hconsole, cursorPosition, 0, listFood_listLenght(foodList) + 10);
                    printf("Errore: nessun cibo selezionato.");
                    Sleep(3000);
                    return 20;
                }
            }

            else if (menuItem == listFood_listLenght(foodList) + 1)
                return 20;
            else
            {
                cinfo.dwSize = SM_CYCURSOR;
                cinfo.bVisible = TRUE;
                SetConsoleCursorInfo(hconsole, &cinfo);

                do
                {
                    _gotoXY(hconsole, cursorPosition, 60, menuItem + 8);
                    printf("Qta': ");
                    scanf("%i", &foodQta);
                    _clearBuffer();
                    if ((foodQta < 0) || (foodQta > listFood_checkAvailability(foodQta,
                                                                               listFood_findFoodByPosition(menuItem,
                                                                                                           foodList))))
                    {
                        _gotoXY(hconsole, cursorPosition, 65, menuItem + 8);
                        printf("  Errore: quantita' non valida.");
                        Sleep(3000);
                        _gotoXY(hconsole, cursorPosition, 65, menuItem + 8);
                        printf("                                  ");
                    }
                } while ((foodQta < 0) || (foodQta > listFood_checkAvailability(foodQta,
                                                                                listFood_findFoodByPosition(menuItem,
                                                                                                            foodList))));

                foodQtaArray[menuItem] = foodQta;

                cinfo.dwSize = SM_CYCURSOR;
                cinfo.bVisible = FALSE;
                SetConsoleCursorInfo(hconsole, &cinfo);
            }
            break;
        }
    }

    //Sezione inserimento lista cibi in driver
    for (int i = 0; i < listFood_listLenght(foodList); i++)
    {
        if (foodQtaArray[i])
        {
            FoodList *selectedItem = listFood_findFoodByPosition(i, foodList);

            driver->items = listFood_insertToListItemsForDriver(driver->items, foodQtaArray[i], selectedItem);
        }
    }

    //Sezione riepilogo
    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Riepilogo");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-----------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Merce da consegnare:");
    _gotoXY(hconsole, cursorPosition, 0, 6);

    FoodList *driverList = driver->items;
    int yPos = 8;
    int totalWeight = 0;
    int ctrl;
    char answer;

    while (driverList)
    {
        totalWeight += driverList->item.foodWeight * driverList->quantity;
        _gotoXY(hconsole, cursorPosition, 10, yPos);
        printf("Prodotto: %s\n", driverList->item.name);
        printf("          Brand: %s\n", driverList->item.brand);
        printf("          Prezzo: %.2lf x %d\n", driverList->item.price, driverList->quantity);
        printf("          Peso ordine: %d\n", driverList->item.foodWeight * driverList->quantity);
        driverList = driverList->next;
        yPos += 5;
    }

    _gotoXY(hconsole, cursorPosition, 0, yPos + 1);
    printf("Prezzo totale: %.2lf", listFood_calculateTotalPrice(driver->items));

    _gotoXY(hconsole, cursorPosition, 0, yPos + 2);
    printf("Peso totale: %d", totalWeight);

    _gotoXY(hconsole, cursorPosition, 0, yPos + 3);
    ctrl = graph_findDijkstraPath(graph, startIslandPosition, destinationIslandPosition,
                                  listFood_calculateTotalWeight(driver->items) + driver->vehicleWeight);

    if (ctrl)
    {
        cinfo.dwSize = SM_CYCURSOR;
        cinfo.bVisible = TRUE;
        SetConsoleCursorInfo(hconsole, &cinfo);

        do
        {
            _gotoXY(hconsole, cursorPosition, 19, yPos + 15);
            printf("           ");
            _gotoXY(hconsole, cursorPosition, 0, yPos + 15);
            printf("Sei sicuro/a [s/n]? ");
            scanf("%c", &answer);
            _clearBuffer();
        } while ((answer != 'n') && (answer != 'N') && (answer != 's') && (answer != 'S'));

        cinfo.dwSize = SM_CYCURSOR;
        cinfo.bVisible = FALSE;
        SetConsoleCursorInfo(hconsole, &cinfo);

        if ((answer == 's') || (answer == 'S'))
        {
            driverList = driver->items;
            while (driverList)
            {
                listFood_updateAvailability(driverList, driverList->quantity, foodList);
                driverList = driverList->next;
            }

            driver_printDeliveryHistory(driver, graph->nodeArray[startIslandPosition]->key,
                                        graph->nodeArray[destinationIslandPosition]->key,
                                        listFood_calculateTotalPrice(driver->items));

            listFood_freeList(&(driver->items));
            driver->items = NULL;
            return 20;
        }
        else
        {
            listFood_freeList(&(driver->items));
            driver->items = NULL;
            return 20;
        }
    }
    else
    {
        listFood_freeList(&(driver->items));
        driver->items = NULL;
        _gotoXY(hconsole, cursorPosition, 0, yPos + 15);
        system("pause");
        return 20;
    }
}

int display_deliveryHistory(HANDLE hconsole, Driver *driver)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Storico consegne");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-------------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);

    driver_printDeliveryHistoryByUsername(driver->username);

    system("pause");
    return 20;
}

int display_driverInfo(HANDLE hconsole, Driver *driver)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Informazioni sull'account");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("--------------------------");

    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Username:");
    _gotoXY(hconsole, cursorPosition, 30, 4);
    printf("%s", driver->username);

    _gotoXY(hconsole, cursorPosition, 0, 5);
    printf("Password:");
    _gotoXY(hconsole, cursorPosition, 30, 5);
    printf("%s", driver->password);

    _gotoXY(hconsole, cursorPosition, 0, 6);
    printf("Codice Fiscale:");
    _gotoXY(hconsole, cursorPosition, 30, 6);
    printf("%s", driver->cf);

    _gotoXY(hconsole, cursorPosition, 0, 7);
    printf("Nome:");
    _gotoXY(hconsole, cursorPosition, 30, 7);
    printf("%s", driver->name);

    _gotoXY(hconsole, cursorPosition, 0, 8);
    printf("Cognome:");
    _gotoXY(hconsole, cursorPosition, 30, 8);
    printf("%s", driver->surname);

    _gotoXY(hconsole, cursorPosition, 0, 9);
    printf("email:");
    _gotoXY(hconsole, cursorPosition, 30, 9);
    printf("%s", driver->email);

    _gotoXY(hconsole, cursorPosition, 0, 10);
    printf("Telefono:");
    _gotoXY(hconsole, cursorPosition, 30, 10);
    printf("%s", driver->telephone);

    _gotoXY(hconsole, cursorPosition, 0, 11);
    printf("Indirizzo residenza:");
    _gotoXY(hconsole, cursorPosition, 30, 11);
    printf("%s", driver->address);

    _gotoXY(hconsole, cursorPosition, 0, 12);
    printf("Denominazione del veicolo:");
    _gotoXY(hconsole, cursorPosition, 30, 12);
    printf("%s", driver->vehicleName);

    _gotoXY(hconsole, cursorPosition, 0, 13);
    printf("Targa del veicolo:");
    _gotoXY(hconsole, cursorPosition, 30, 13);
    printf("%s", driver->plate);

    _gotoXY(hconsole, cursorPosition, 0, 14);
    printf("Peso del veicolo (Kg):");
    _gotoXY(hconsole, cursorPosition, 30, 14);
    printf("%d", driver->vehicleWeight);

    _gotoXY(hconsole, cursorPosition, 0, 16);
    system("pause");
    return 20;
}

int display_deleteDriver(HANDLE hconsole, Driver **driver)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;

    char answer;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Eliminazione driver");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("-------------------");

    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    do
    {
        _gotoXY(hconsole, cursorPosition, 19, 6);
        printf("           ");
        _gotoXY(hconsole, cursorPosition, 0, 5);
        printf("Sei sicuro/a [s/n]? ");
        scanf("%c", &answer);
        _clearBuffer();
    } while ((answer != 'n') && (answer != 'N') && (answer != 's') && (answer != 'S'));

    if ((answer == 's') || (answer == 'S'))
    {
        if (driver_deleteDriverByUsername((*driver)->username))
        {
            *driver = NULL;
            _gotoXY(hconsole, cursorPosition, 0, 8);
            printf("Eliminazione riuscita.");
            Sleep(3000);

            cinfo.dwSize = SM_CYCURSOR;
            cinfo.bVisible = FALSE;
            SetConsoleCursorInfo(hconsole, &cinfo);

            return 0;
        }
        else
        {
            _gotoXY(hconsole, cursorPosition, 0, 8);
            printf("Errore: eliminazione driver non riuscita.");
            Sleep(3000);
            cinfo.dwSize = SM_CYCURSOR;
            cinfo.bVisible = FALSE;
            SetConsoleCursorInfo(hconsole, &cinfo);

            return 20;
        }
    }
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &cinfo);
    return 20;
}

int display_newDriver(HANDLE hconsole)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;

    Driver *tempDriver = driver_newDriver();
    char answer;

    char username[DRIVER_MAX_USERNAME_LENGTH];
    char password[DRIVER_MAX_PASSWORD_LENGTH];
    char cf[DRIVER_MAX_CF_LENGTH];
    char name[DRIVER_MAX_NAME_SURNAME_LENGTH];
    char surname[DRIVER_MAX_NAME_SURNAME_LENGTH];
    char email[DRIVER_MAX_EMAIL_LENGTH];
    char telephone[DRIVER_MAX_TELEPHONE_LENGTH];
    char address[DRIVER_MAX_ADDRESS_LENGTH];
    int weight;
    char vehicleName[DRIVER_MAX_VEHICLENAME_LENGTH];
    char plate[DRIVER_MAX_PLATE_LENGTH];

    //Stampa delle frasi a video//
    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Registrazione nuovi driver");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("--------------------------");
    _gotoXY(hconsole, cursorPosition, 0, 3);
    printf("Benvenuto/a sulla piattaforma.");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    printf("Inserisci i seguenti dati:");

    //Immissione e controlla dati
    do
    {
        _gotoXY(hconsole, cursorPosition, 14, 6);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 6);
        printf("Username: ");
        scanf(" %[^\n]s", username);
        _clearBuffer();
        if (!driver_checkUsername(username))
        {
            _gotoXY(hconsole, cursorPosition, 5, 8);
            printf("Errore: l'username e' gia' presente e/o troppo lungo.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 8);
            printf("                                                     ");
        }
    } while (!driver_checkUsername(username));

    do
    {
        _gotoXY(hconsole, cursorPosition, 14, 7);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 7);
        printf("Password: ");
        scanf(" %[^\n]s", password);
        _clearBuffer();
        if (!driver_checkPassword(password))
        {
            _gotoXY(hconsole, cursorPosition, 5, 9);
            printf("Errore: la password non e' valida.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 9);
            printf("                                  ");
        }
    } while (!driver_checkPassword(password));

    do
    {
        _gotoXY(hconsole, cursorPosition, 20, 8);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 8);
        printf("Codice fiscale: ");
        scanf(" %[^\n]s", cf);
        _clearBuffer();
        if (!driver_checkCf(cf))
        {
            _gotoXY(hconsole, cursorPosition, 5, 10);
            printf("Errore: il codice fiscale non valido e/o gia' esistente.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 10);
            printf("                                                        ");
        }
    } while (!driver_checkCf(cf));

    do
    {
        _gotoXY(hconsole, cursorPosition, 10, 9);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 9);
        printf("Nome: ");
        scanf(" %[^\n]s", name);
        _clearBuffer();
        if (!driver_checkName(name))
        {
            _gotoXY(hconsole, cursorPosition, 5, 11);
            printf("Errore: il nome non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 11);
            printf("                              ");
        }
    } while (!driver_checkName(name));

    do
    {
        _gotoXY(hconsole, cursorPosition, 13, 10);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 10);
        printf("Cognome: ");
        scanf(" %[^\n]s", surname);
        _clearBuffer();
        if (!driver_checkName(surname))
        {
            _gotoXY(hconsole, cursorPosition, 5, 12);
            printf("Errore: il cognome non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 12);
            printf("                                 ");
        }
    } while (!driver_checkName(surname));

    do
    {
        _gotoXY(hconsole, cursorPosition, 11, 11);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 11);
        printf("Email: ");
        scanf(" %[^\n]s", email);
        _clearBuffer();
        if (!driver_checkEmail(email))
        {
            _gotoXY(hconsole, cursorPosition, 5, 13);
            printf("Errore: l'email non e' valida o e' gia' esistente.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 13);
            printf("                                                  ");
        }
    } while (!driver_checkEmail(email));

    do
    {
        _gotoXY(hconsole, cursorPosition, 14, 12);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 12);
        printf("Telefono: ");
        scanf(" %[^\n]s", telephone);
        _clearBuffer();
        if (!driver_checkTelephone(telephone))
        {
            _gotoXY(hconsole, cursorPosition, 5, 14);
            printf("Errore: il telefono non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 14);
            printf("                                  ");
        }
    } while (!driver_checkTelephone(telephone));

    do
    {
        _gotoXY(hconsole, cursorPosition, 15, 13);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 13);
        printf("Indirizzo: ");
        scanf(" %[^\n]s", address);
        _clearBuffer();
        if (!driver_checkAddress(address))
        {
            _gotoXY(hconsole, cursorPosition, 5, 15);
            printf("Errore: l'indirizzo non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 15);
            printf("                                  ");
        }
    } while (!driver_checkAddress(address));

    do
    {
        _gotoXY(hconsole, cursorPosition, 22, 14);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 14);
        printf("Nome del veicolo: ");
        scanf(" %[^\n]s", vehicleName);
        _clearBuffer();
        if (!driver_checkVehicleName(vehicleName))
        {
            _gotoXY(hconsole, cursorPosition, 5, 16);
            printf("Errore: il nome del veicolo non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 16);
            printf("                                          ");
        }
    } while (!driver_checkVehicleName(vehicleName));

    do
    {
        _gotoXY(hconsole, cursorPosition, 18, 15);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 15);
        printf("Peso veicolo: ");
        scanf("%d", &weight);
        _clearBuffer();
        if (weight < DRIVER_MIN_VEHICLE_WEIGHT)
        {
            _gotoXY(hconsole, cursorPosition, 5, 17);
            printf("Errore: il peso non e' valido.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 17);
            printf("                               ");
        }
    } while (weight < DRIVER_MIN_VEHICLE_WEIGHT);

    do
    {
        _gotoXY(hconsole, cursorPosition, 23, 16);
        printf("                            ");
        _gotoXY(hconsole, cursorPosition, 5, 16);
        printf("Targa del veicolo: ");
        scanf(" %[^\n]s", plate);
        _clearBuffer();
        if (!driver_checkPlate(plate))
        {
            _gotoXY(hconsole, cursorPosition, 5, 18);
            printf("Errore: la targa del veicolo non e' valida.");
            Sleep(3000);
            _gotoXY(hconsole, cursorPosition, 5, 18);
            printf("                                           ");
        }
    } while (!driver_checkPlate(plate));

    do
    {
        _gotoXY(hconsole, cursorPosition, 19, 20);
        printf("           ");
        _gotoXY(hconsole, cursorPosition, 0, 20);
        printf("Sei sicuro/a [s/n]? ");
        scanf("%c", &answer);
        _clearBuffer();
    } while ((answer != 'n') && (answer != 'N') && (answer != 's') && (answer != 'S'));

    if ((answer == 's') || (answer == 'S'))
    {
        tempDriver->username = strdup(username);
        tempDriver->password = strdup(password);
        tempDriver->cf = strdup(cf);
        tempDriver->name = strdup(name);
        tempDriver->surname = strdup(surname);
        tempDriver->email = strdup(email);
        tempDriver->telephone = strdup(telephone);
        tempDriver->address = strdup(address);
        tempDriver->vehicleName = strdup(vehicleName);
        tempDriver->vehicleWeight = weight;
        tempDriver->plate = strdup(plate);

        if (driver_registration(tempDriver))
        {
            _gotoXY(hconsole, cursorPosition, 0, 22);
            printf("Inserimento riuscito.");
            Sleep(3000);
            cinfo.dwSize = SM_CYCURSOR;
            cinfo.bVisible = FALSE;
            SetConsoleCursorInfo(hconsole, &cinfo);
            return 0;
        }
        else
        {
            _gotoXY(hconsole, cursorPosition, 0, 22);
            printf("Errore: inserimento non riuscito.");
            Sleep(3000);
            cinfo.dwSize = SM_CYCURSOR;
            cinfo.bVisible = FALSE;
            SetConsoleCursorInfo(hconsole, &cinfo);
            return 0;
        }
    }
    else
    {
        _gotoXY(hconsole, cursorPosition, 0, 22);
        printf("Inserimento annullato.");
        Sleep(3000);
        cinfo.dwSize = SM_CYCURSOR;
        cinfo.bVisible = FALSE;
        SetConsoleCursorInfo(hconsole, &cinfo);
        return 0;
    }
}

int display_islandsList(HANDLE hconsole, AdjacencyGraph *graph)
{
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.dwSize = SM_CYCURSOR;
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hconsole, &cinfo);

    COORD cursorPosition;

    system("cls");
    _gotoXY(hconsole, cursorPosition, 0, 0);
    printf("Mappa");
    _gotoXY(hconsole, cursorPosition, 0, 1);
    printf("--------------------------");
    _gotoXY(hconsole, cursorPosition, 0, 4);
    for (int i = 0; i < graph->arrayLength; i++)
    {
        if (graph->nodeArray[i])
        {
            AdjacencyListNode *temp = graph->nodeArray[i]->adjacencyListHead;

            printf("Isola: %s\n", graph->nodeArray[i]->name);
            while (temp)
            {
                printf("    Collegamento con: %s\n", graph->nodeArray[graph_findPositionByKey(graph->nodeArray,
                                                                                              graph->arrayLength,
                                                                                              temp->destinationKey,
                                                                                              NULL)]
                                                         ->name);
                printf("        Peso max consentito: %d\n", temp->supportedWeight);
                temp = temp->next;
            }
            printf("\n");
        }
    }

    system("pause");
    return 0;
}