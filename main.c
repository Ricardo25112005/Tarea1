#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

//codigo para ejecutar el programa.    gcc -o tarea1 main.c list.c 
typedef struct{
    int ID;
    int rut;
    char name[31];
    int prioridad;
    char hora[6];
    char Estado[10];
}tipoTicket;

void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
    puts("Presione una tecla para continuar...");
    getchar(); // Consume el '\n' del buffer de entrada
    getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
limpiarPantalla();
puts("========================================");
puts("     Sistema de Gestión de Tickets");
puts("========================================");
puts("1) Registrar Ticket");
puts("2) Asignar prioridad a Ticket");
puts("3) Mostrar lista de espera");
puts("4) Atender al siguiente Ticket");
puts("5) Mostrar Tickets por prioridad");
puts("6) Salir");
}  

void obtenerHoraActual(char *hora) {
  time_t t;
  struct tm *tm_info;

  // Obtiene el tiempo actual
  time(&t);
  tm_info = localtime(&t);

  // Formatea la hora en formato HH:MM
  strftime(hora, 6, "%H:%M", tm_info);
}

void registrar_paciente(List *tickets) {
    tipoTicket *auxiliar = malloc(sizeof(tipoTicket));
    if (auxiliar == NULL) {
      printf("Error: No se pudo asignar memoria.\n");
      return;
    }
    printf("Registrar nuevo paciente\n");
    printf("Ingresar Id: ");
    scanf(" %d", &auxiliar->ID);
    printf("Ingresar Rut(sin puntos ni digito verificador): ");
    scanf(" %d", &auxiliar->rut);
    printf("Ingresar nombre del cliente: ");
    scanf(" %s", auxiliar->name);
    getchar();
    obtenerHoraActual(auxiliar->hora);
    auxiliar->prioridad = 0;
    strcpy(auxiliar->Estado, "Pendiente"); 
    push_back(tickets, auxiliar);
    // Aquí implementarías la lógica para registrar un nuevo paciente
}
  
void mostrar_lista_pacientes(List *tickets) {
    if (list_firts(tickets) == NULL) {
        printf("No hay pacientes en espera.\n");
        return;
    }
    else{
        printf("Pacientes en espera: \n");
        tipoTicket *actual = list_firts(tickets);
        while (actual != NULL) {
        if (strcmp(actual->Estado,"Pendiente") == 0)printf("ID: %d, Rut: %d, Nombre: %s, Hora: %s\n",actual->ID, actual->rut, actual->name, actual->hora);
        actual = list_next(tickets);
        }
    }
}

void modificar_ticket(List *tickets) {
    if (list_firts(tickets) == NULL) {
        printf("No hay pacientes en espera.\n");
        return;
    }
    else{
        int idTicket;
        printf("Ingrese el ID del ticket a modificar: ");
        scanf(" %d", &idTicket);
        tipoTicket *actual = list_firts(tickets);
        while (actual != NULL) {
            if (actual->ID == idTicket) {
                printf("Modificar Ticket ID: %d\n", actual->ID);
                printf("Ingresar nueva prioridad: ");
                scanf(" %d", &actual->prioridad);
                break;
            }
            actual = list_next(tickets);
        }
    }
}


int main() {
    char opcion;
    List *Tickets = create_List();
  
    do {
      mostrarMenuPrincipal();
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el salto de línea
      switch (opcion) {
      case '1':
        registrar_paciente(Tickets);
        break;
      case '2':
        modificar_ticket(Tickets); 
        // Lógica para asignar prioridad
        break;
      case '3':
        mostrar_lista_pacientes(Tickets);
        break;
      case '4':
        // Lógica para atender al siguiente ticket
        break;
      case '5':
        // Lógica para mostrar tickets por prioridad
        break;
      case '6':
        puts("Saliendo del sistema de gestión de Tickets...");
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
      }
      presioneTeclaParaContinuar();
  
    } while (opcion != '6');
    cleanList(Tickets); // prueba numero 1
  
    return 0;
}
  