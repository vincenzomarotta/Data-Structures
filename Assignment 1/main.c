#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "./Librerie/utente.h"
#include "./Librerie/menu.h"
#include "./Librerie/appuntamento.h"
#include "./Librerie/piattaforma.h"
#include "./Librerie/laboratorio.h"


int main(){
    while(1){
        menuPrincipale();
        int scelta;
        printf("Inserire numero operazione: ");
        scanf("%d", &scelta);
        switch (scelta){
            case 1:
                registrazione();
                break;
            case 2:
                login();
                break;
            case 3:
                piattaforma();
                break;
            case 4:
                infoCovid();
                break;
            case 5:
                printf("\nGrazie per aver usato il sistema, a presto!\n");
                return 0;
            default:
                printf("Operazione non valida, riprova.\n");
                system("PAUSE");
                break;
        }
    }
}
