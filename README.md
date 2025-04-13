Sistema de gestion de Tickets
=====
---
Para esta Programa de gestion de tickets se implementara una **lista** para organizar los tickets que se van registrando y en caso de modificar su prioridad mpverlos a donde sea necesario, esto utilizando la siguiente estructura (ListaEnlazada Doble):
````c
typedef struct Node Node;
typedef struct List List;

struct Node{
    void * ticket; 
    Node * next;
    Node * prev;
};

struct List{
    Node * head;
    Node * tail;
    Node * current;
};
````
---
Este programa tiene como finalidad crear una cola de tickets ordenados con prioridad y por orden de registro,registrando cada ticket, modificando la prioridad de los tickets, mostrando la lista de pendientes, procesar el siguiente ticket de la listade pendientes y mostrando la lista ordenada por prioridad devidido en 5 secciones: 

1. Registro de ticket: En esta parte se llama a la funcion `void registrar_ticket(List * tickets)`, funcion la cual recive la lista de tickets, crea un auxiliar al cual se lee el id a travez de una funcion llamada `unsigned long long leerID(List * tickets)` la cual lee el ID en formato de string y verifica que sea numerica, en caso de no ser numerica se pide que se ingrese un ID numerico o en caso de ya existir ese ID en la lista se pide que se reingrense un ID diferente. Lee el rut a travez de la funcion `unsigned long long leerRut()` la cual lee el rut en modo de string y verifica que sea un numero, en caso de no serlo se pide que se reingrese un rut valido. Se lee un numbre en formato string, y se lee la hora local del computador a travez de la funcion `void obtenerHoraActual(char * hora)`, lugeo se le asigna prioridad 1 y estado pendiente, para finalmente hacer un `push_back(List * tickets, tipoTicket * ticket)` para agregarlo al final de la lista.  
2. Modificar Ticket: En esta seccion la funcion a llamar es `void modificar_ticket(List * tickets)` la cual muestra en pantalla todos los tickets pendientes a travez de la funcion `void mostrar_lista_Pendientes(List * tickets)` para luego preguntar por el ID del ticket que se quiere modificar, en caso de estar en la lista se pregunta por la nueva prioridad, si la prioridad nueva no esta entre los valores de 1 a 3 se pide que se reingrese, si se ingresa la prioridad igual a la actual no se modifica el ticket, en otro caso se elimina de la lista para reingresar en la posicion deseada.

3. Mostrar lista pendientes: en esta parte se llama a la funcion `void mostrar_lista_Pendientes(List * tickets)` la cual muestra todos los ticket pendientes, con sus atributos de Id, rut, nombre y hora de registro, en caso de estar vacia se muestra el mensaje de "No hay tickets en espera.".

4. Atender ticket: se llama a la funcion `void atender_ticket(List * Tickets)` la cual muestra en pantalla el ticket con todos sus atributos, y cambia su estado de pendiente a atendido, generndo que no pueda ser mostrado en mostrar lista de pendientes.

5. Mostrar lista por prioridad: en tes parte se llama a la funcion `void mostrar_lista_prioridad(Tickets)` la cual muestra toda la lista de tickets ordenada por su prioridad, sin tener en cuenta su estado.

Luego para compilar y ejecutar:

    gcc main.c list.c -o tarea1
    ./tarea1 
