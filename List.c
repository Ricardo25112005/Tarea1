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
    if (list->current == NULL) return NULL;
    if(list->current->prev != NULL){
        list->current = list->current->prev;
        return list->current->ticket;    
    }
    return NULL;
}

void * push_back(List * list, void * ticket){
    list->current = list->tail;
    push_current(list, ticket);
}

void * push_front(List * list, void * ticket){
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

void * push_current(List * list, void * ticket){
    Node * nuevo = create_node(ticket);
    if (list->head == NULL){
        list->head = nuevo;
        list->current = nuevo;
        list->tail = nuevo;
    }
    else if (list->current == list->tail){
        list->tail->next = nuevo;
        nuevo->prev = list->tail;
        list->tail = nuevo;
    }
    else{
        nuevo->next = list->current->next;
        nuevo->prev = list->current;
        list->current->next->prev = nuevo;
        list->current->next = nuevo;
    }
}

void * pop_front(List *list) {
    list->current = list->head;
    return pop_current(list);
}

void * pop_back(List *list) {
    list->current = list->tail;
    return pop_current(list);
}

void * pop_current(List *list) {
    if (list == NULL || list->head == NULL || list->current == NULL) return NULL;
    void * ticket = list->current->ticket;
    Node *nodo_eliminar = list->current;
    if (list->current == list->head){
        list->head = list->head->next;
        list->current = list->head;
        list->head->prev = NULL;
    }
    else if (list->current == list->tail){
        list->tail = list->tail->prev;
        list->current = list->tail;
        list->tail->next = NULL;
    }
    else{
        Node * izq = list->current->prev;
        Node * der = list->current->next;
        izq->next = der;
        der->prev = izq;
        list->current = der;
    }
    free(nodo_eliminar);
    return ticket;
}

void  cleanList(List * list) {
    while (list->head != NULL) {
        pop_front(list);
    }
}