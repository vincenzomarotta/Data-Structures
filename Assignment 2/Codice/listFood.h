#ifndef listFood_h
#define listFood_h

#define FOOD_MAX_NAME_LENGTH 51
#define FOOD_MAX_BRAND_LENGTH 51
#define FOOD_MAX_RECORD_LENGTH 710

typedef struct Food{
  int barcode;
  char *name;
  int available;
  int foodWeight;
  char *brand;
  double price;
  struct Food *next;
  } Food;


typedef struct FoodList{
  Food item;
  int quantity;
  struct FoodList *next;
} FoodList;

//FUNZIONI GENERICHE///////////////////////////////////
int listFood_isEmpty(FoodList *head);
void listFood_listPrint(FoodList *head);
void listFood_freeList(FoodList **head);
//////////////////////////////////////////////////////




//FUNZIONI SU LISTA ALIMENTI DISPONIBILI IN MAGAZZINO//
FoodList *listFood_findPosition(int position, FoodList *head, int cnt);
FoodList *listFood_findFoodByPosition(int position, FoodList *head);
int listFood_listLenght(FoodList *head);
int listFood_loadConfirmedFoodListFromDb(FILE *db, FoodList **head);
int listFood_loadFoodListFromDb(FoodList **head);
int listFood_checkAvailabilityByFoodBarcode(FoodList **head,int barcode, int quantityTaken);
int listFood_addNewFood(FoodList **head,int barcode, char *name, int available, int foodWeight, char *brand, double price);
int listFood_removeFoodFromListByBarcode(FoodList**head,FoodList *prev, int barcode);//prev � passato come NULL inizialmente!
int listFood_writeOnDbFoodListWithoutFoodByBarcode(FoodList **head, int barcode);
int listFood_updateDbFoodListBeforeCloseSystem(FoodList **head);
FoodList *listFood_findFoodByBarcode(FoodList *head,int barcode);
////////////////////////////////////////////////////////




//FUNZIONI SU LISTA ALIMENTI TRASPORTATI DAL DRIVER//
int listFood_calculateTotalWeight(FoodList *items);
FoodList *listFood_insertToListItemsForDriver(FoodList *items, int quantityTaken, FoodList *cpyNodo);
int listFood_checkAvailability(int foodQta, FoodList *nodo);
int listFood_updateAvailability(FoodList *node, int quantityTaken, FoodList *head);
double listFood_calculateTotalPrice(FoodList *items);

///////////////////////////////////////////////////////

#endif
