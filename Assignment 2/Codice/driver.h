#include <stdio.h>
#ifndef driver_h
#define driver_h

/********** CONSTANTS **********/
#define DRIVER_MIN_FIELD_LENGTH 5 // Misura minima per tutti i campi di stringhe, eccetto per nome, cognome e codice fiscale 
#define DRIVER_MAX_USERNAME_LENGTH 51 // 50 char + '\0'
#define DRIVER_MAX_PASSWORD_LENGTH 51 // 50 char + '\0'
#define DRIVER_MAX_CF_LENGTH 17 // 16 char + '\0'
#define DRIVER_MIN_NAME_SURNAME_LENGTH 2 // -> Misura minima dei campi Nome e Cognome
#define DRIVER_MAX_NAME_SURNAME_LENGTH 51 // 50 char + '\0'
#define DRIVER_MAX_EMAIL_LENGTH 71 // 70 char + '\0'
#define DRIVER_MAX_TELEPHONE_LENGTH 11 // 10 char + '\0'
#define DRIVER_MAX_ADDRESS_LENGTH 101 // 100 char + '\0'
#define DRIVER_MAX_VEHICLENAME_LENGTH 51 // 50 char + '\0'
#define DRIVER_MIN_VEHICLE_WEIGHT 500
#define DRIVER_MAX_PLATE_LENGTH 9 // 8 char + '\0'
#define DRIVER_MAX_RECORD_LENGTH 301 // 300 char + '\0'
#define FILE_LOGIN_DRIVER "db/login_driver.txt"
#define FILE_ORDER_HISTORY "db/order_history.txt"

/********** TYPES **********/

typedef struct FoodList FoodList;

// Struttura del Driver
typedef struct Driver
{
  char *username;
  char *password;
  char *cf; 
  char *name;
  char *surname;
  char *email;
  char *telephone;
  char *address;
  int vehicleWeight;
  char *vehicleName;
  char *plate;
  FoodList *items;
  struct Driver *next;
} Driver;

/********** PROTOTYPES **********/

/* FUNZIONI LISTA */
Driver *driver_newDriver();
Driver *driver_append(Driver *list, Driver *newDriver);
Driver *driver_createList();
int driver_printDriverList(Driver *list);
int driver_deleteDriverByUsername(char *username);

/* FUNZIONI REGISTRAZIONE */
Driver *driver_initializeDriver();
int driver_checkUsernameExistence(char *username);
int driver_checkEmailExistence(char *email);
int driver_checkCfExistence(char *cf);
int driver_isAllAlpha(char *string, int len);
int driver_isAllDigit(char *string, int len);
int driver_checkUsername(char *username);
int driver_checkPassword(char *password);
int driver_checkCf(char *cf);
int driver_checkName(char *name);
int driver_checkEmail(char *email);
int driver_checkTelephone(char *telephone);
int driver_checkAddress(char *address);
int driver_checkVehicleName(char *vehicleName);
int driver_checkPlate(char *plate);
int driver_registration(Driver *newDriver);

/* FUNZIONI LOGIN */
int driver_login(char *username, char *password, Driver **driver);

/* FUNZIONI STORICO */
int driver_printDeliveryHistory(Driver *d, int startIsland, int destinationIsland, double totalPrice);
int driver_printDeliveryHistoryByUsername(char *username);


#endif
