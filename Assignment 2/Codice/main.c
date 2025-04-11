#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "graph.h"
#include "display.h"
#include "driver.h"
#include "listFood.h"

void initializeGraph(FILE **db, AdjacencyGraph **graph);
void initializeFoodList(FoodList **head);
void saveAndCloseGraph(AdjacencyGraph **graph);
void saveAndCloseFoodList(FoodList **head);

int main(void)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Driver *verifiedDriver = NULL;
    FoodList *head = NULL;

    FILE *db = NULL;
    AdjacencyGraph *graph = NULL; 

    initializeGraph(&db, &graph);
    initializeFoodList(&head);


    int running = 1;
    int nextMenu = 0; //Ricordarsi di portarlo a 0

    while(running)
    {
        switch (nextMenu)
        {
            case 0: //Menu principale
                nextMenu = display_mainMenu(hconsole);
                break;

            case 10: //Menu login driver
                nextMenu = display_driverLogin(hconsole, &verifiedDriver);
                break;

            case 20: //Menu principale driver
                nextMenu = display_driverMenu(hconsole, verifiedDriver);
                break;

            case 30: //Menu programmazione consegna
                nextMenu = display_driverDeliveryProgram(hconsole, verifiedDriver, graph, head);
                break;

            case 35: //Menu storico consegne
                nextMenu = display_deliveryHistory(hconsole, verifiedDriver);
                break;

            case 37: //Menu informazioni account driver
                nextMenu = display_driverInfo(hconsole, verifiedDriver);
                break;

            case 40: //Menu eliminazione driver
                nextMenu = display_deleteDriver(hconsole, &verifiedDriver);
                break;

            case 50: //Menu nuovo driver
                nextMenu = display_newDriver(hconsole);
                break;

            case 60: //Menu mappa
                nextMenu = display_islandsList(hconsole, graph);
                break;

            case 10000:
                running = 0;
                break;
        }
    }

    saveAndCloseGraph(&graph);
    saveAndCloseFoodList(&head);
    return 0;
}

void initializeGraph(FILE **db, AdjacencyGraph **graph)
{
    *db = graph_openDbToRead("graph");
    *graph = graph_newGraph(0);
    graph_loadGraphFromDb(*db, *graph, NULL, NULL);
    graph_closeDb(db);
}

void initializeFoodList(FoodList **head)
{
    listFood_loadFoodListFromDb(head);
}

void saveAndCloseGraph(AdjacencyGraph **graph)
{
    graph_deleteGraph(graph);
}

void saveAndCloseFoodList(FoodList **head)
{
    listFood_updateDbFoodListBeforeCloseSystem(head);
    listFood_freeList(head);
}