// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "macros.h"
#include "linked_list.h"
#include "auxiliary.h"
#include "functions.h"

t_ll *create_list()
{
    // allocate memory
    t_ll *list = malloc(sizeof(t_ll));
    if (!list) {
        fprintf(stderr, "Malloc failed.\n");
        exit(-1);
    }

    // set pointers to NULL
    list->head = NULL;
    list->tail = NULL;
    list->next = NULL;
    list->prev = NULL;
    list->data = NULL;
    list->size = 0;

    return list;
}

t_ll *create_card(t_ll *deckList, int num, char *symb)
{
    t_ll *card = create_list();

    t_data *new_card = malloc(sizeof(t_data));
    if (!new_card) {
        fprintf(stderr, "Malloc failed.\n");
        free_all(deckList);
        exit(-1);
    }

    // assign the insput number & symbol to the data field of the card
    new_card->num = num;
    strcpy(new_card->symb, symb);
    card->data = new_card;
    card->next = NULL;
    card->prev = NULL;

    return card;
}

t_ll *go_to_node(t_ll *list, int idx)
{
    t_ll *aux = list->head;
    while (idx--) {
        aux = aux->next;
    }
    return aux;
}

void free_list(t_ll *list)
{   // free all elemenets in list
    t_ll *aux = list->head;
    for (int i = 0; i < list->size; i++) {
        t_ll *next = aux->next;
        free(aux->data);
        free(aux);
        aux = next;
    }
    free(list);  // free list itself
}

void free_all(t_ll *deckList)
{
    t_ll *deck = deckList->head;
    for (int i = 0; i < deckList->size; i++)
    {
        t_ll *next = deck->next;
        free_list(deck);
        deck = next;
    }
    free(deckList);
}

void add_at_end_of_list(t_ll *list, t_ll *node)
{
    if (!list->head) {  // list is empty, so new node becomes head
        list->head = node;
    } else {  // new node is connected after tail
        list->tail->next = node;
        node->prev = list->tail;
    }
    list->tail = node;  // new node becomes tail
    list->size++;  // increase list size
}
