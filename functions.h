// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// allocates memory for a new deck and adds the cards in it,
// then appends the deck to the deck list
void add_deck(t_ll *, int);

// reads values for the cards, checks if they are valid, allocates
// memory for a new card and then append the card to the deck
void add_cards_to_deck(t_ll *, t_ll *, int);

// deletes a deck from the deck list, freeing the memory
void delete_deck(t_ll *, int);

// deletes a card from a deck, freeing the memory
void delete_card(t_ll *, int , int);

// shuffles a deck by inverting its 2 halves
void shuffle_deck(t_ll *);

// creates a new deck by merging 2 of them
// the merged decks are then deleted from the deck list
// and the new deck is appended to the deck list
void merge_decks(t_ll *, int , int);

// creates a new deck by splitting a deck at a certain
// card index. the new deck is inserted in the list
void split_deck(t_ll *, int , int);

// reverses the order of the cards in the deck
void reverse_deck(t_ll *, int);

// shows the cards in a deck when given its index
void show_deck(t_ll *, int);

// shows the cards in a deck when given a pointer to the deck
void show_cards_in_deck(t_ll *);

// shows the cards in all decks
void show_all(t_ll *);

// sorts the cards in the deck in ascending order
void sort_deck(t_ll *, int);
#endif  // FUNCTIONS_H_
