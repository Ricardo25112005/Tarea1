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

void *pop_front(List *list) {
    if (list->head == NULL) return NULL; 
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) list->tail = NULL;
    free(temp);
}

void  cleanList(List * list) {
    while (list->head != NULL) {
        pop_front(list);
    }
}