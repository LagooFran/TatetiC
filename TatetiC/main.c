#include <stdio.h>
#include <stdlib.h>

int main()
{
    int seleccion;
    int salir = 0;
    ///Menu para tateti
    while(salir!=1){
        printf("TatetiC!\n\n");
        printf("1.Comenzar a jugar\n2.Ver puntuaciones anteriores\n3.Salir\n");
        scanf("%d", &seleccion);


        switch(seleccion){
            case 1:
                printf("op1");
                break;
            case 2:
                printf("op2");
                break;
            case 3:
                printf("Saliendo...");
                salir = 1;
                break;
            default:
                printf("Opcion Invalida\n");
                break;
        }
    }
}
