// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

// creates a new list by allocating memory
t_ll *create_list();

// creates a new card by allocating memory and also
// assigning it the desired number & symbol
t_ll *create_card(t_ll *, int , char *);

// traverses a linked list to the k th desired node
t_ll *go_to_node(t_ll *, int k);

// frees memory for a deck
void free_list(t_ll *);

// frees memory for the whole deck list
void free_all(t_ll *);

// adds a new node at the end of a list
void add_at_end_of_list(t_ll *list, t_ll *node);
#endif  // LINKED_LIST_H_
