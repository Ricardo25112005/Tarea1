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

void registrar_ticket(List *tickets) {
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
    auxiliar->prioridad = 1;
    strcpy(auxiliar->Estado, "Pendiente"); 
    push_back(tickets, auxiliar);
    // Aquí implementarías la lógica para registrar un nuevo paciente
}
  
void mostrar_lista_tickets(List *tickets) {
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
      printf("No hay tickets en espera.\n");
      return;
  }

  int idTicket;
  printf("Ingrese el ID del ticket a modificar: ");
  scanf(" %d", &idTicket);

  tipoTicket *actual = list_firts(tickets);
  while (actual != NULL) {
      if (actual->ID == idTicket) {
          printf("Modificar Ticket ID: %d\n", actual->ID);
          printf("Ingresar nueva prioridad(2 para media y 3 para alta): ");
          int nuevaPrioridad;
          scanf(" %d", &nuevaPrioridad);
          // Elimina el nodo actual de la lista
          tipoTicket *ticketModificado = pop_current(tickets);
          // Actualiza la prioridad del ticket
          ticketModificado->prioridad = nuevaPrioridad;
          // Inserta el nodo en la posición correcta según la prioridad
          tipoTicket *aux = list_firts(tickets);
          if (ticketModificado->prioridad > aux->prioridad) {push_front(tickets, ticketModificado); return;}
          while (aux != NULL && aux->prioridad >= ticketModificado->prioridad) {
              aux = list_next(tickets);
          }
          if (aux == NULL) {
              // Si no hay un nodo con menor prioridad, inserta al final
              push_back(tickets, ticketModificado);
          } else {
              // Inserta antes del nodo actual
              list_prev(tickets);
              push_current(tickets, ticketModificado);
          }
          printf("El ticket ha sido modificado y reordenado según su prioridad.\n");
          return;
      }
      actual = list_next(tickets);
  }

  printf("No se encontró un ticket con el ID especificado.\n");
}

void mostrar_lista_prioridad(List *tickets) {
    if (list_firts(tickets) == NULL) {
        printf("No hay tickets Registrados.\n");
        return;
    }
    else{
        printf("Tickets por prioridad: \n");
        tipoTicket *actual = list_firts(tickets);
        while (actual != NULL) {
            printf("ID: %d, Rut: %d, Nombre: %s, Hora: %s, Estado: %s, Prioridad: %d\n",actual->ID, actual->rut, actual->name, actual->hora, actual->Estado, actual->prioridad);
            actual = list_next(tickets);
        }
    }
}

void atender_ticket(List *tickets) {
    if (list_firts(tickets) == NULL) {
        printf("No hay Tickets en espera.\n");
        return;
    }
    tipoTicket *actual = list_firts(tickets);
    while (actual != NULL) {
        if (strcmp(actual->Estado,"Pendiente") == 0){
            printf("Atendiendo Ticket ID: %d, Rut: %d, Nombre: %s, Hora: %s\n",actual->ID, actual->rut, actual->name, actual->hora);
            strcpy(actual->Estado, "Atendido"); 
            return;
        }
        actual = list_next(tickets);
    }
    printf("No hay Tickets pendientes para atender.\n");
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
        registrar_ticket(Tickets);
        break;
      case '2':
        modificar_ticket(Tickets);
        // Lógica para asignar prioridad
        break;
      case '3':
        mostrar_lista_tickets(Tickets);
        break;
      case '4':
        atender_ticket(Tickets);
        // Lógica para atender al siguiente ticket
        break;
      case '5':
        mostrar_lista_prioridad(Tickets);
        // Lógica para mostrar tickets por prioridad
        break;
      case '6':
        puts("Saliendo del sistema de gestión de Tickets...");
        if (Tickets != NULL) {
          cleanList(Tickets);
          free(Tickets);
          Tickets = NULL; // Asegúrate de que el puntero sea NULL después de liberarlo
        }
        exit(0);
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
      }
      presioneTeclaParaContinuar();
  
    } while (opcion != '6');
    //cleanList(Tickets); // prueba numero 1
  
    return 0;
}
  