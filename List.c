#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

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

List * create_List(){
    List * list = (List *)malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

Node * create_node(void * ticket){
    Node * node = (Node *)malloc(sizeof(Node));
    if (node == NULL) exit(EXIT_FAILURE);
    node->ticket = ticket;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void * list_firts(List * list){
    if (list == NULL|| list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->ticket;
}

void * list_next(List *list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL; 
    list->current = list->current->next;
    return list->current->ticket;
}

void * list_prev(List *list){
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL; 
    list->current = list->current->prev;
    return list->current->ticket;
}

void push_back(List * list, void * ticket){
    if (list == NULL) {
      return; // Lista no inicializada
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
      return; // Fallo en la asignación de memoria
    }
    newNode->ticket = ticket;
    newNode->next = NULL;
    if (list->tail == NULL) { // Si la lista está vacía
      list->head = newNode;
      list->tail = newNode;
    } else {
      list->tail->next = newNode;
      list->tail = newNode;
    }
}

void push_front(List * list, void * ticket){
    Node * nuevo = create_node(ticket);
    if (list->head != NULL){
        list->head->prev = nuevo;
        nuevo->next = list->head;
        list->head = nuevo;
    }
    else{
        list->head = nuevo;
        list->tail = nuevo;
        list->current = nuevo;
    }
}

void push_current(List * list, void * ticket){
    Node * nuevo = create_node(ticket);
    if (list == NULL || nuevo == NULL || list->current == NULL) return;
    if (list->head == NULL) {
        list->head = nuevo;
        list->current = nuevo;
        list->tail = nuevo;
    } else if (list->current == list->tail) {
        list->tail->next = nuevo;
        nuevo->prev = list->tail;
        list->tail = nuevo;
    } else if (list->current != NULL) {
        nuevo->next = list->current->next;
        nuevo->prev = list->current;
        if (list->current->next != NULL) {
            list->current->next->prev = nuevo;
        }
        list->current->next = nuevo;
    } else {
        // Caso: list->current es NULL (error)
        fprintf(stderr, "Error: list->current es NULL en push_current.\n");
        free(nuevo);
        return;
    }
}

void * pop_front(List *list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
    list->tail = NULL;
    }
    void *data = temp->ticket;
    free(temp);
    return data;
}

void * pop_back(List *list) {
    list->current = list->tail;
    return pop_current(list);
}

void * pop_current(List *list) {
    if (list == NULL || list->current == NULL) {
        return NULL; 
    }
    if (list->current == list->head) {
        return pop_front(list);
    }
    Node *temp = list->head;
    while (temp != NULL && temp->next != list->current) {
        temp = temp->next;
    }
    temp->next = list->current->next;
    if (list->current == list->tail) {
        list->tail = temp;
    }
    void *data = list->current->ticket;
    free(list->current);
    list->current = NULL;
    return data;
}
void list_sortedInsert(List *L, void *data, int (*lower_than)(void *data1, void *data2)) {
    if (L == NULL) {
      return; // Lista no inicializada
    }
  
    // Caso especial: inserción al principio o en lista vacía
    if (L->head == NULL || lower_than(data, L->head->ticket)) {
      push_front(L, data);
      return;
    }
  
    // Caso general: encontrar la posición correcta para insertar
    Node *current = L->head;
    while (current->next != NULL && !lower_than(data, current->next->ticket)) {
      current = current->next;
    }
  
    // Preparar para usar list_pushCurrent
    L->current = current;
  
    // Insertar el nodo en la posición actual
    push_current(L, data);
  }

void  cleanList(List * list) {
    while (list->head != NULL) {
        pop_front(list);
    }
}