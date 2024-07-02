#include <stdio.h>
#include "funcionest.h"
#include <string.h>

#define TAMANOClien 30
int nombresingresados=0;

void ingresarClientes(char clientes[][2][40], int tamanoclien, int *numClientes){
    int i, cantidad;
    printf("Ingrese la cantidad de clientes que desea ingresar:\n ");
    scanf("%d", &cantidad);
    if (*numClientes + cantidad > tamanoclien) {
        printf("Error: No hay suficiente espacio en la matriz para almacenar %d clientes.\n", cantidad);
        fflush(stdin);
        return;
    }
    for (i = *numClientes; i < *numClientes + cantidad; i++) {
        printf("Ingrese el nombre del cliente %d: \n", i+1);
        fflush(stdin);
        scanf("%s", clientes[i][0]);
        printf("Ingrese la cedula del cliente %d: \n", i+1);
        scanf("%s", clientes[i][1]);
        fflush(stdin);
        int existe = 0;
        for (int j = 0; j < *numClientes; j++) {
            if (strcmp(clientes[j][1], clientes[i][1]) == 0) {
                existe = 1;
                break;
            }
        }
        if (existe) {
            printf("La cedula ya se ha ingresado anteriormente.\n");
            i--;
            fflush (stdin);
        }
    }
    *numClientes += cantidad;
}

void buscarPorTamano(int *numHabitacion,char habitaciones[][3][40],double precios[]){
    char tipo[40];
    printf("Ingrese el tamano de habitacion que desea buscar: ");
    scanf("%s",tipo);
    printf("#\t\tTamano\t\tHotel\t\tPrecio\n");
    int encontrado=0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1],tipo)==0) {
            printf("%s\t\t%s\t\t%s\t\t%lf\n",habitaciones[i][0],habitaciones[i][1],habitaciones[i][2],precios[i]);
            encontrado=1;
        }
    } 
    if (!encontrado) {
        printf("No se encontro ese tipo de habitacion\n");
    } else {
        printf("Elija la habitacion que desea reservar: ");
        scanf("%d", numHabitacion);
    }
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]){
    char hotel[40];
    printf("Ingrese el nombre del hotel que desea buscar: ");
    scanf("%s",hotel);
    printf("#\t\tTamano\t\tHotel\t\tPrecio\n");
    int encontrado=0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2],hotel)==0) {
            printf("%s\t\t%s\t\t%s\t\t%lf\n",habitaciones[i][0], habitaciones[i][1], habitaciones [i][2], precios[i]);
            encontrado=1;
        }
    }
    if (!encontrado) {
        printf("\nNo se encontro el hotel que deseas buscar\n");
    } else {
        printf("Elija la habitacion que desea reservar: ");
        scanf("%d",numHabitacion); 
    }
}

void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[TAMANOClien][2][40], int reservas[10][4], double precios[9], int tamanoclien, int *numClientes) {
    int clienteIndex;
    char cedula[40];
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula);
    clienteIndex = -1;

    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }
    
    if (clienteIndex == -1) {
        printf("Cliente no encontrado.\n");
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = clienteIndex;
            reservas[i][1] = numHabitacion;
            reservas[i][2] = 1;
            reservas[i][3] = 0;
            printf("Reserva realizada exitosamente.\n");
            return;
        }
    }
    printf("No hay espacio para nuevas reservas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[10][4], int tamanoclien){
    char cedula[40];
    printf("Ingrese la cedula del cliente para buscar reserva: ");
    scanf("%s",cedula);
    int clienteIndex = -1;
    for (int i = 0; i < tamanoclien; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }
    if (clienteIndex == -1) {
        printf("No se encontro el cliente.\n");
        *numReserva = -1;
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == clienteIndex) {
            *numReserva = i;
            return;
        }
    }
    printf("No se encontraron reservas para el cliente.\n");
    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9], char clientes[TAMANOClien][2][40], int tamanoclien){
    if (numReserva == -1) return;
    int clienteIndex = reservas[numReserva][0];
    int habitacionIndex = reservas[numReserva][1] - 1;
    printf("Reserva #%d\n", numReserva);
    printf("Cliente: %s\n", clientes[clienteIndex][0]);
    printf("Cedula: %s\n", clientes[clienteIndex][1]);
    printf("Habitacion: %s\n", habitaciones[habitacionIndex][0]);
    printf("Tamano: %s\n", habitaciones[habitacionIndex][1]);
    printf("Hotel: %s\n", habitaciones[habitacionIndex][2]);
    printf("Precio: %.2f\n", precios[habitacionIndex]);
    printf("Estado de pago: %s\n", reservas[numReserva][3] == 1 ? "Pagado" : "No Pagado");
}

void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9], char clientes[TAMANOClien][2][40], int tamanoclien) {
    if (numReserva == -1) return;
    reservas[numReserva][3] = 1;
    printf("La reserva ha sido pagada.\n");
}
