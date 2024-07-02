#include <stdio.h>
#include "funcionest.h"
#define tamanoclien 30

int main(int argc, char *argv[]) {
    char clientes[tamanoclien][2][40] = {{0}};
    int numClientes = 0;

    char habitaciones[9][3][40] = {{"1","simple","Dan Carlton"},
                                   {"2","doble","Dan Carlton"},
                                   {"3","triple","Dan Carlton"},
                                   {"4","simple","Swissotel"},
                                   {"5","doble","Swissotel"},
                                   {"6","triple","Swissotel"},
                                   {"7","simple","Sheraton"},
                                   {"8","doble","Sheraton"},
                                   {"9","triple","Sheraton"}};

    double precios[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};

    int reservas[10][4] = {{-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0},
                           {-1, -1, -1, 0}};

    int opcion, numHabitacion, numReserva;

    FILE *clientesFile = fopen("clientes.txt", "r");
    if (clientesFile != NULL) {
        while (fscanf(clientesFile, "%s %s", clientes[numClientes][0], clientes[numClientes][1]) != EOF) {
            numClientes++;
        }
        fclose(clientesFile);
    }

    FILE *reservasFile = fopen("reservas.txt", "r");
    if (reservasFile != NULL) {
        int i = 0;
        while (fscanf(reservasFile, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]) != EOF) {
            i++;
        }
        fclose(reservasFile);
    }

    do {
        printf("Escoja una opcion:\n1.Ingresar clientes\n2.Buscar Habitacion\n3.Realizar reserva\n4.Ver reservas\n5.Pagar Reserva\n>>");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            ingresarClientes(clientes, tamanoclien, &numClientes);
            //Guarda los datos de los clientes
            clientesFile = fopen("clientes.txt", "w"); 
            if (clientesFile == NULL) {
                printf("Error al abrir el archivo de clientes\n");
                return 1;
            }
            for (int i = 0; i < numClientes; i++) {
                fprintf(clientesFile, "%s %s\n", clientes[i][0], clientes[i][1]);
            }
            fclose(clientesFile);
            break;
        case 2:
            printf("1.Por tamano\n2.Por Hotel\n>>");
            scanf("%d", &opcion);
            switch (opcion) {
            case 1:
                buscarPorTamano(&numHabitacion, habitaciones, precios);
                break;
            case 2:
                buscarHotel(&numHabitacion, habitaciones, precios);
                break;
            default:
                break;
            }
            break;
        case 3:
            realizarReserva(numHabitacion, habitaciones, clientes, reservas, precios, tamanoclien, &numClientes);
            break;
        case 4:
            buscarReservaPorCedula(&numReserva, clientes, reservas, tamanoclien);
            imprimirReserva(numReserva, reservas, habitaciones, precios, clientes, tamanoclien);
            break;
        case 5:
            buscarReservaPorCedula(&numReserva, clientes, reservas, tamanoclien);
            pagarReserva(numReserva, reservas, habitaciones, precios, clientes, tamanoclien);
            break;
        default:
            break;
        }
        printf("Desea elegir otra opcion \n1 = si \t\t2 = no\n");
        scanf("%d", &opcion);
    } while (opcion == 1);

    // Guarda todos los datos ingresados en el archivo de texto reservas.txt
    reservasFile = fopen("reservas.txt", "w");
    if (reservasFile == NULL) {
        printf("Error opening reservas file\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] != -1) {
            fprintf(reservasFile, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
        }
    }

    fclose(reservasFile);

    return 0;
}
