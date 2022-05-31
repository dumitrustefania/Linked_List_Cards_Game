// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "macros.h"
#include "linked_list.h"
#include "auxiliary.h"
#include "functions.h"

int read_tokens(char tokens[TOKENS_MAX][COMMAND_MAX])
{
    char c;
    scanf("%c", &c);
    if (c != ' ')  // if it exists any token
        return 0;

    char str[COMMAND_MAX];
    fgets(str, COMMAND_MAX, stdin);
    if (str[strlen(str) - 1] == '\n')  // remove trailing newline
        str[strlen(str) - 1] = '\0';

    char *p = strtok(str, " ");
    int count = 0;
    while (p)
    {
        strcpy(tokens[count], p);  // tokenize the string
        p = strtok(NULL, " ");
        count++;
    }

    return count;
}

int card_num(t_ll *card)
{
    t_data card_val = *(t_data *)card->data;
    return card_val.num;
}

char *card_symb(t_ll *card)
{
    t_data card_val = *(t_data *)card->data;
    char *symb = malloc(SYMB_MAX);
    strcpy(symb, card_val.symb);
    return symb;
}

void print_card(t_ll *card)
{
    t_data card_val = *(t_data *)card->data;
    printf("%d %s\n", card_val.num, card_val.symb);
}

t_ll *copy_card(t_ll *deckList, t_ll *card)
{
    t_data card_val = *(t_data *)card->data;
    t_ll *copy = create_card(deckList, card_val.num, card_val.symb);
    return copy;
}

int cmp(t_ll *card, t_ll *min)
{
    if (card_num(card) < card_num(min))  // first check their numbers
        return 1;

    if (card_num(card) == card_num(min))  // if numbers are equal
    {
        // extract their symbols
        char *symb1 = card_symb(card);
        char *symb2 = card_symb(min);

        // check which one is smaller relative to the symbol
        if (symb1[0] == 'H' ||
           (symb1[0] == 'S' && symb2[0] != 'H') ||
           (symb1[0] == 'D' && symb2[0] != 'H' && symb2[0] != 'S')){
                 free(symb1);
                free(symb2);
               return 1;
           }
        free(symb1);
        free(symb2);
    }
    return 0;
}

t_ll *search_min_card(t_ll *deck, int start_idx)
{
    t_ll *min = go_to_node(deck, start_idx);

    // loop through cards from i to end to find minimum
    t_ll *aux = min;
    for (int i = start_idx + 1; i < deck->size; i++)
    {   aux = aux->next;
        if (cmp(aux, min))
            min = aux;
    }
    return min;
}
