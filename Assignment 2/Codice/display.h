#ifndef display_h
#define display_h

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

typedef struct Driver Driver;
typedef struct AdjacencyGraph AdjacencyGraph;
typedef struct FoodList FoodList;

int display_mainMenu(HANDLE hconsole);
int display_driverLogin(HANDLE hconsole, Driver **driver);
int display_driverMenu(HANDLE hconsole, Driver *driver);
int display_driverDeliveryProgram(HANDLE hconsole, Driver *driver, AdjacencyGraph *graph, FoodList *foodList);
int display_deliveryHistory(HANDLE hconsole, Driver *driver);
int display_driverInfo(HANDLE hconsole, Driver *driver);
int display_deleteDriver(HANDLE hconsole, Driver **driver);
int display_newDriver(HANDLE hconsole);
int display_islandsList(HANDLE hconsole, AdjacencyGraph *graph);

#endif