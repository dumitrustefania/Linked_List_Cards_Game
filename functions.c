// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "macros.h"
#include "linked_list.h"
#include "auxiliary.h"
#include "functions.h"

void add_deck(t_ll *deckList, int no_cards)
{
    t_ll *deck = create_list();
    add_cards_to_deck(deckList, deck, no_cards);
    add_at_end_of_list(deckList, deck);
}

void add_cards_to_deck(t_ll *deckList, t_ll *deck, int no_cards)
{
    while (no_cards) {
        int num;
        char symb[SYMB_MAX];
        char str[COMMAND_MAX];

        fgets(str, TOKENS_MAX * COMMAND_MAX, stdin);
        str[strlen(str) - 1] = '\0';
        char *p = strtok(str, " ");
        num = atoi(p);  // input number
        p = strtok(NULL, " ");
        strcpy(symb, p);  // input symbol

        // checks if card is valid
        if ((num < 1 || num > 14) ||
            (strcmp(symb, "HEART") && strcmp(symb, "CLUB") &&
             strcmp(symb, "DIAMOND") && strcmp(symb, "SPADE"))) {
            INVALID_CARD;
            continue;
        }

        t_ll *card = create_card(deckList, num, symb);  // creates the new card
        add_at_end_of_list(deck, card);
        no_cards--;
    }
}

void delete_deck(t_ll *deckList, int deck_idx)
{
    t_ll *remove_deck;
    if (deck_idx == 0) {  // if deck removed is head, recompute the head
        remove_deck = deckList->head;
        deckList->head = remove_deck->next;
        if (deckList->head)
            deckList->head->prev = NULL;
    } else if (deck_idx == deckList->size - 1) {
        // if deck removed is tail, recompute the tail
        remove_deck = deckList->tail;
        deckList->tail = deckList->tail->prev;
        deckList->tail->next = NULL;
    } else {  // connect neigbors of removed deck
        remove_deck = go_to_node(deckList, deck_idx);
        remove_deck->prev->next = remove_deck->next;
        remove_deck->next->prev = remove_deck->prev;
    }

    free_list(remove_deck);  // free memory for removed deck
    deckList->size--;
}

void delete_card(t_ll *deckList, int deck_idx, int card_idx)
{
    t_ll *deck = go_to_node(deckList, deck_idx);

    if (card_idx >= deck->size || card_idx < 0) {
        CARD_INDEX_OUT_OF_BOUNDS(deck_idx);
        return;
    }

    if (deck->size == 1) {
        // if I delete the last card in deck, I also delete the deck
        delete_deck(deckList, deck_idx);
        printf("The card was successfully deleted from deck %d.\n", deck_idx);
        return;
    }

    t_ll *remove_card;
    if (card_idx == 0) {
        // if card removed is head, recompute the head
        remove_card = deck->head;
        deck->head = remove_card->next;
        deck->head->prev = NULL;
    } else if (card_idx == deck->size - 1) {
        // if card removed is tail, recompute the tail
        remove_card = deck->tail;
        deck->tail = deck->tail->prev;
        deck->tail->next = NULL;
    } else {  // connect neigbors of removed card
        remove_card = go_to_node(deck, card_idx);
        remove_card->prev->next = remove_card->next;
        remove_card->next->prev = remove_card->prev;
    }

    // free memory for removed card
    free(remove_card->data);
    free(remove_card);
    deck->size--;

    printf("The card was successfully deleted from deck %d.\n", deck_idx);
}

void shuffle_deck(t_ll *deck)
{
    if (deck->size == 1)  // can't shuffle if there is 1 card
        return;

    // pointer to head of first half
    t_ll *first_half = deck->head;

    // pointer to card before head of second half
    t_ll *second_half = go_to_node(deck, deck->size / 2 - 1);

    // inverses the 2 halves
    deck->head = second_half->next;
    deck->tail->next = first_half;
    first_half->prev = deck->tail;
    deck->tail = second_half;

    deck->tail->next = NULL;
    deck->head->prev = NULL;
}

void merge_decks(t_ll *deckList, int idx1, int idx2)
{
    // find the 2 decks
    t_ll *deck1 = go_to_node(deckList, idx1);
    t_ll *deck2 = go_to_node(deckList, idx2);
    int size1 = deck1->size;
    int size2 = deck2->size;
    t_ll *card1 = deck1->head;
    t_ll *card2 = deck2->head;

    // allocate memory for the new deck
    t_ll *merged_deck = create_list(deckList);

    // merge the decks by copying alternatively a card from the 2 decks
    while (size1 && size2)
    {
        t_ll *copy_card1 = copy_card(deckList, card1);
        t_ll *copy_card2 = copy_card(deckList, card2);

        if (merged_deck->size == 0)
        {
            merged_deck->head = copy_card1;
        }
        else
        {
            merged_deck->tail->next = copy_card1;
            copy_card1->prev = merged_deck->tail;
        }
        merged_deck->tail = copy_card1;

        merged_deck->tail->next = copy_card2;
        copy_card2->prev = merged_deck->tail;
        merged_deck->tail = copy_card2;

        merged_deck->size += 2;
        card1 = card1->next;
        card2 = card2->next;

        size1--;
        size2--;
    }

    // if there are cards left in 1st deck, copy the rest of them
    while (size1)
    {
        t_ll *copy_card1 = copy_card(deckList, card1);
        merged_deck->tail->next = copy_card1;
        copy_card1->prev = merged_deck->tail;
        merged_deck->tail = copy_card1;

        merged_deck->size++;
        card1 = card1->next;
        size1--;
    }

    // if there are cards left in 2nd deck, copy the rest of them
    while (size2)
    {
        t_ll *copy_card2 = copy_card(deckList, card2);
        merged_deck->tail->next = copy_card2;
        copy_card2->prev = merged_deck->tail;
        merged_deck->tail = copy_card2;

        merged_deck->size++;
        card2 = card2->next;
        size2--;
    }

    // deleted the 2 decks, freeing memory
    delete_deck(deckList, idx1);

    if (idx1 < idx2)
        delete_deck(deckList, idx2 - 1);
    else
        delete_deck(deckList, idx2);

    // appends the new deck to the deckList
    add_at_end_of_list(deckList, merged_deck);
}

void split_deck(t_ll *deckList, int deck_idx, int split_idx)
{
    t_ll *deck = go_to_node(deckList, deck_idx);

    if (split_idx >= deck->size || split_idx < 0)
    {
        CARD_INDEX_OUT_OF_BOUNDS(deck_idx);
        return;
    }

    if (split_idx > 0) {  // if index = 0, do nothing
        t_ll *new_deck = create_list(deckList);

        // card where the deck will be split
        t_ll *splitting_card = go_to_node(deck, split_idx - 1);

        // compute the new heads and tails for the 2 decks
        new_deck->head = splitting_card->next;
        new_deck->tail = deck->tail;
        deck->tail = splitting_card;

        new_deck->head->prev = NULL;
        deck->tail->next = NULL;

        new_deck->size = deck->size - split_idx;
        deck->size = split_idx;

        // add the new deck after the one that was split
        if (deckList->tail == deck) {
            deck->next = new_deck;
            new_deck->prev = deck;
            deckList->tail = new_deck;
        } else {
            new_deck->next = deck->next;
            new_deck->prev = deck;
            new_deck->next->prev = new_deck;
            new_deck->prev->next = new_deck;
        }
        deckList->size++;
    }

    printf("The deck %d was successfully split by index %d.\n",
            deck_idx, split_idx);
}

void reverse_deck(t_ll *deckList, int deck_idx)
{
    t_ll *deck = go_to_node(deckList, deck_idx);
    if (deck->size == 1)
        return;

    t_ll *aux = deck->head, *tmp = NULL;

    // reverse a doubly linked list
    deck->tail = deck->head;
    while (aux) {
        tmp = aux->prev;
        aux->prev = aux->next;
        aux->next = tmp;
        aux = aux->prev;
    }
    deck->head = tmp->prev;
    deck->tail->next = NULL;
    deck->head->prev = NULL;
}

void show_deck(t_ll *deckList, int deck_idx)
{
    t_ll *deck = go_to_node(deckList, deck_idx);
    printf("Deck %d:\n", deck_idx);
    show_cards_in_deck(deck);
}

void show_cards_in_deck(t_ll *deck)
{   // traverse deck to print all cards
    t_ll *aux = deck->head;
    for (int i = 0; i < deck->size; i++) {
        printf("\t");
        print_card(aux);
        aux = aux->next;
    }
}

void show_all(t_ll *deckList)
{   // traverse deckList to print all decks
    t_ll *deck = deckList->head;
    for (int i = 0; i < deckList->size; i++) {
        printf("Deck %d:\n", i);
        show_cards_in_deck(deck);
        deck = deck->next;
    }
}

void sort_deck(t_ll *deckList, int deck_idx)
{
    t_ll *deck = go_to_node(deckList, deck_idx);
    t_ll *aux = deck->head;

    // at each iteration, I search for the minimum card
    // from position i to the end of the deck.
    // the minimum card is then put in list at position i
    for (int i = 0; i < deck->size; i++)
    {   // finds the minimum card from position i to the end
        t_ll *card = search_min_card(deck, i);

        // if card was already at position i, do nothing
        if ((i!= 0 && card == aux->next) || (i == 0 && card == aux)){
            if (i != 0)
                aux = aux->next;
            continue;
        }

        // connect neighbors of minimum card
        if (card->prev)
            card->prev->next = card->next;
        else
            deck->head = card->next;

        if (card->next)
               card->next->prev = card->prev;
        else
            deck->tail = card->prev;

        // insert the minimum card at position i
        if (i == 0)
        {   card->next = deck->head;
            deck->head->prev = card;
            deck->head = card;
        }
        else if (i == deck->size - 1)
        {
            card->prev = deck->tail;
            deck->tail->next = card;
            deck->tail = card;
        }
        else
        {   card->next = aux->next;
            card->next->prev = card;
            aux->next = card;
            card->prev = aux;
        }

        aux = card;
    }
}
