// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef AUXILIARY_H_
#define AUXILIARY_H_

// reads the tokens given as input after the command, in order
// to check if they are the expected number
int read_tokens(char[TOKENS_MAX][COMMAND_MAX]);

// returns the number written on a card
int card_num(t_ll *);

// returns the symbol written on a card
char *card_symb(t_ll *);

// prints the number & symbol on a card
void print_card(t_ll *);

// creates a copy of a card that has the same number & symbol
t_ll *copy_card(t_ll *, t_ll *);

// compares 2 cards for the sorting function
int cmp(t_ll *, t_ll *);

// searches for the relative minimum card from a certain
// index to the end of the deck
t_ll *search_min_card(t_ll *, int);
#endif  // AUXILIARY_H_
