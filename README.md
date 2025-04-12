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

1. Registro de ticket: en esta parte se llama a la funcion `void registrar_ticket(List * tickets)`, funcion la cual recive la lista de tickets, crea un auxiliar al cual se lee el id a travez de una funcion llamada `unsigned long long leerID(List * tickets)` la cual lee el ID en formato de string y verifica que sea numerica, en caso de no ser numerica se pide que se ingrese un ID numerico o en caso de ya existir ese ID en la lista se pide que se reingrense un ID diferente. Lee el rut a travez de la funcion `unsigned long long leerRut()` la cual lee el rut en modo de string y verifica que sea un numero, en caso de no serlo se pide que se reingrese un rut valido. Se lee un numbre en formato string, y se lee la hora local del computador a travez de la funcion `void obtenerHoraActual(char * hora)`, lugeo se le asigna prioridad 1 y estado pendiente, para finalmente hacer un `push_back(List * tickets, tipoTicket * ticket)` para agregarlo al final de la lista.  
2.
Programe las funciones void * firstList(List * list) y void * nextList(List * list).

La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.
Programe las funciones void * lastList(List * list) y void * prevList(List * list).

La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.
Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.

Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.

Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

Las funciones pushBack, popFront y popBack se pueden implementar usando popCurrent y pushCurrent (búsquelas en el código).

Por lo tanto, ya tiene implementado su primer TDA!
Pruebe su implementación
Revise el ejemplo en el archivo main.c.

Luego para compilar y ejecutar:

    gcc main.c list.c -o tarea1
    ./tarea1 
