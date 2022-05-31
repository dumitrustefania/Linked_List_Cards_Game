**Dumitru Bianca Stefania**
**312CA**

## Homework #1 - Data Structures - Now You See Me

## General description and notes:

-The program is meant to operate with multiple linked list, that represent 
cards, decks of cards and a list of decks. All of them are represented in memory
as doubly linked lists, making acces to any element fast and easy.

    * A card is an element that stores 2 values: a number [1-14] and a symbol
[HEART/CLUB/SPADE/DIAMOND].
    * A deck is a linked list whose nodes are cards.
    * Multiple decks form the list of decks.

- All the elements in the linked lists are dinamically alocated in memory,
using malloc(), realloc() and free() functions from the stdlib.h library.

- I defined 2 data structures: "t_data" (that stores an int - the number represented
on the card, and a string - the symbol) and "t_ll" (a data structure that incorporates
all fuctionalities of both a list and a node inside of it).

## Commands:
- There are 13 possible commands that can be recieved from input:

1) ADD_DECK deck_idx
	- allocates dinamically the necessary memory for the deck
	- reads the values for the cards and stores them inside the deck
	- adds the new deck at the end of the list of decks

2) DEL_DECK deck_idx
	- deletes the deck from the list of decks
    - frees the memory for the deck and the cards inside of it

3) DEL_CARD deck_idx card_idx
	- deletes a card from a certain deck
    - frees the memory for the card

4) ADD_CARDS deck_idx num
	- reads the values for the new cards and stores them at 
        the end of the deck

5) DECK_NUMBER
	- outputs the number of decks present in the list of decks

6) DECK_LEN deck_idx
	- outputs the number of cards present in a certain deck

7) SHUFFLE_DECK deck_idx
	- shuffles the cards by inverting the 2 halves of a deck

8) MERGE_DECKS deck_idx1 deck_idx2
	- allocates memory for a new deck, that will be the merged one
    - adds cards one by one into the new deck from each of the given decks
    - deletes the old decks and frees their memory
	- adds the new deck at the end of the list of decks

9) SPLIT_DECK deck_idx card_idx
	- allocates memory for a new deck, that will be the split one
	- moves the cards starting with the one at card_idx, into the new deck
    - adds the new deck into the list of decks immediatly after the old deck

10) REVERSE_DECK deck_idx
    - reverses the order of cards in a certain deck
	
11) SHOW_DECK deck_idx
    - outputs all cards in a certain deck

12) SHOW_ALL
    - outputs for each deck in the list of decks, all the cards inside of it

13) SORT_DECK deck_idx
    - sorts the cards in a certain deck, after a certain criteria
        - ascending after the number on the cards
        - if 2 cards have the same number, priority of the symbols will be
            HEART < SPADE < DIAMOND < CLUB

14)EXIT
    - frees the memory for all the decks in the list
	- frees the memory for the list
	- stops the program
