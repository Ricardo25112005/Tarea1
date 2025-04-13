#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"

//codigo para ejecutar el programa.    gcc -o tarea1 main.c list.c 
typedef struct{
    unsigned long long ID;
    unsigned long long rut;
    char nombre[121];
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

int esNumero(const char *cadena) {
  for (int i = 0; cadena[i] != '\0'; i++) {
      if (!isdigit(cadena[i])) {
          return 0; 
      }
  }
  return 1;
}

bool idRepetido(List *tickets, unsigned long long id) {
  if (list_firts(tickets) == NULL) {
      return false;
  }
  tipoTicket *actual = list_firts(tickets);
  while (actual != NULL) {
      if (actual->ID == id) {
          return true;
      }
      actual = list_next(tickets);
  }
  return false;
}

unsigned long long leerID(List *tickets, List *ticketsAtendidos) {
  char entrada[100];
  char *endptr; // Puntero para detectar errores en strtol
  unsigned long long id;

  while (1) {
      printf("Ingrese un ID: ");
      scanf("%s", entrada);
      getchar(); 
      id = strtol(entrada, &endptr, 10);
      if (idRepetido(tickets, id) == true || idRepetido(ticketsAtendidos, id) == true) {
        printf("El ID ya existe. Por favor, ingrese un ID diferente.\n");
        continue;
      }
      if (*endptr == '\0' && id > 0) { // Asegura que toda la cadena sea un número, que sea positivo y que no este repetido
          return id;
      } else {
          printf("Entrada inválida. Por favor, ingrese un ID válido (numérico y positivo).\n");
      }
  }
}

unsigned long long leerRut() {
  char entrada[100];
  char *endptr; // Puntero para detectar errores en strtol
  unsigned long long id;

  while (1) {
      printf("Ingrese un rut (sin puntos ni digito verificador): ");
      scanf("%s", entrada);
      getchar();
      id = strtol(entrada, &endptr, 10);
      if (*endptr == '\0' && id > 0) { // Asegura que toda la cadena sea un número y que sea positivo
          return id;
      } else {
          printf("Entrada inválida. Por favor, ingrese un rut válido (numérico y positivo).\n");
      }
  }
}

void registrar_ticket(List *tickets, List *ticketsAtendidos) {
    tipoTicket *auxiliar = malloc(sizeof(tipoTicket));
    if (auxiliar == NULL) {
     printf("Error: No se pudo asignar memoria.\n");
      return;
    }
    limpiarPantalla();
    printf("Registrar nuevo ticket\n");
    auxiliar->ID = leerID(tickets, ticketsAtendidos);
    auxiliar->rut = leerRut();
    printf("Ingresar nombre del cliente: ");
    fgets(auxiliar->nombre, 121, stdin);
    auxiliar->nombre[strcspn(auxiliar->nombre, "\n")] = 0;
    obtenerHoraActual(auxiliar->hora);
    auxiliar->prioridad = 1;
    strcpy(auxiliar->Estado, "Pendiente"); 
    push_back(tickets, auxiliar);
    // Aquí implementarías la lógica para registrar un nuevo paciente
}
  
void mostrar_lista_Pendientes(List *tickets) {
    limpiarPantalla();
    if (list_firts(tickets) == NULL) {
        printf("No hay tickets en espera.\n");
        return;
    }
    else{
        printf("Tickets en espera: \n");
        tipoTicket *actual = list_firts(tickets);
        while (actual != NULL) {
        if (strcmp(actual->Estado,"Pendiente") == 0)printf("ID: %llu, Rut: %llu, Nombre: %s, Hora: %s\n",actual->ID, actual->rut, actual->nombre, actual->hora);
        actual = list_next(tickets);
        }
    }
}

int lower_than(void *data1, void *data2) {
    tipoTicket *ticket1 = (tipoTicket *)data1;
    tipoTicket *ticket2 = (tipoTicket *)data2;

    // Comparar por prioridad (prioridad más alta tiene mayor valor)
    return ticket1->prioridad > ticket2->prioridad;
}

void modificar_ticket(List *tickets) {
    limpiarPantalla();
    if (list_firts(tickets) == NULL) {
        printf("No hay tickets en espera.\n");
        return;
    }
    if (list_firts(tickets) == NULL) {
        printf("No hay tickets pendientes.\n");
        return;
    }
    mostrar_lista_Pendientes(tickets);
    unsigned long long idTicket;
    printf("Ingrese el ID del ticket a modificar: ");
    scanf(" %llu", &idTicket);
    tipoTicket *actual = list_firts(tickets);
    while (actual != NULL) {
        if (actual->ID == idTicket) {
            limpiarPantalla();
            printf("Modificar Ticket ID: %llu\n", actual->ID);
            printf("Prioridad actual: %d\n", actual->prioridad);
            printf("Ingresar nueva prioridad (1 para Baja, 2 para Media y 3 para Alta): ");
            int nuevaPrioridad;
            scanf(" %d", &nuevaPrioridad);
            if (nuevaPrioridad < 1 || nuevaPrioridad > 3) {
                printf("Prioridad inválida. Debe ser 1, 2 o 3.\n");
                return;
            }
            if (nuevaPrioridad == actual->prioridad) {
                printf("La prioridad no ha cambiado.\n");
                return;
            }
            tipoTicket *ticketModificado = pop_current(tickets);
            if (ticketModificado == NULL) {
                printf("Error al eliminar el ticket.\n");
                return;
            }
            ticketModificado->prioridad = nuevaPrioridad;
            list_sortedInsert(tickets, ticketModificado, lower_than);
            printf("El ticket ha sido modificado y reordenado según su prioridad.\n");
            return;
        }
        actual = list_next(tickets);
    }
    printf("No se encontró un ticket con el ID especificado.\n");
}


void mostrar_lista_prioridad(List *tickets, List *ticketsAtendidos) {
    limpiarPantalla();
    if (list_firts(tickets) == NULL && list_firts(ticketsAtendidos) == NULL) {
        printf("No hay tickets Registrados.\n");
        return;
    }
    else{
        tipoTicket *actual = list_firts(tickets);
        if (list_firts(tickets) == NULL) {
            printf("No hay tickets pendientes.\n");
            printf("Tickets atendidos por prioridad: \n");
            actual = list_firts(ticketsAtendidos);
            while (actual != NULL) {
                printf("ID: %llu, Rut: %llu, Nombre: %s, Hora: %s, Estado: %s, Prioridad: %d\n",actual->ID, actual->rut, actual->nombre, actual->hora, actual->Estado, actual->prioridad);
                actual = list_next(ticketsAtendidos);
            }
        }
        else if (list_firts(ticketsAtendidos) == NULL) {
            printf("No hay tickets atendidos.\n");
            printf("Tickets pendientes por prioridad: \n");
            tipoTicket *actual = list_firts(tickets);
            while (actual != NULL) {
                printf("ID: %llu, Rut: %llu, Nombre: %s, Hora: %s, Estado: %s, Prioridad: %d\n",actual->ID, actual->rut, actual->nombre, actual->hora, actual->Estado, actual->prioridad);
                actual = list_next(tickets);
            }
        }
        else{
            printf("Tickets pendientes por prioridad: \n");
            tipoTicket *actual = list_firts(tickets);
            while (actual != NULL) {
                printf("ID: %llu, Rut: %llu, Nombre: %s, Hora: %s, Estado: %s, Prioridad: %d\n",actual->ID, actual->rut, actual->nombre, actual->hora, actual->Estado, actual->prioridad);
                actual = list_next(tickets);
            }
            printf("Tickets atendidos por prioridad: \n");
            actual = list_firts(ticketsAtendidos);
            while (actual != NULL) {
                printf("ID: %llu, Rut: %llu, Nombre: %s, Hora: %s, Estado: %s, Prioridad: %d\n",actual->ID, actual->rut, actual->nombre, actual->hora, actual->Estado, actual->prioridad);
                actual = list_next(ticketsAtendidos);
            }
        }
    }
}


void atender_ticket(List *tickets, List *ticketsAtendidos){
    limpiarPantalla();
    if (list_firts(tickets) == NULL) {
        printf("No hay Tickets en espera.\n");
        return;
    }
    tipoTicket *actual = list_firts(tickets);
    while (actual != NULL) {
        if (strcmp(actual->Estado,"Pendiente") == 0){
            printf("Atendiendo Ticket ID: %llu, Rut: %llu, Nombre: %s, Hora: %s\n",actual->ID, actual->rut, actual->nombre, actual->hora);
            strcpy(actual->Estado, "Atendido");
            tipoTicket *ticketAtendido = pop_current(tickets);
            list_sortedInsert(ticketsAtendidos, ticketAtendido, lower_than);
            printf("El ticket ha sido atendido y movido a la lista de Tickets atendidos.\n"); 
            return;
        }
        actual = list_next(tickets);
    }
    printf("No hay Tickets pendientes para atender.\n");
}


int main() {
    char opcion;
    List *TicketsPendientes = create_List();
    List *TicketsAtendidos = create_List();
    do {
      mostrarMenuPrincipal();
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el salto de línea
      switch (opcion) {
      case '1':
        registrar_ticket(TicketsPendientes, TicketsAtendidos);
        break;
      case '2':
        modificar_ticket(TicketsPendientes);
        // Lógica para asignar prioridad
        break;
      case '3':
        mostrar_lista_Pendientes(TicketsPendientes);
        break;
      case '4':
        atender_ticket(TicketsPendientes, TicketsAtendidos);
        // Lógica para atender al siguiente ticket
        break;
      case '5':
        mostrar_lista_prioridad(TicketsPendientes, TicketsAtendidos);
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
    cleanList(TicketsPendientes);
    free(TicketsPendientes);
    cleanList(TicketsAtendidos);
    free(TicketsAtendidos);
    return 0;
}
  